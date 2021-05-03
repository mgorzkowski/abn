#!/bin/bash

# Simple wrapper for docker that use only one container and provide handy way to attach to started container

script_name="docker_it.sh"

container_name="abn-container"
image_name="abn-image"

destination_path="/var/local/abn"


usage() {
	echo "Usage: $script_name (clean | launch | shell | destroy | status | help)"
}

help() {
	echo "Simple wrapper for docker that use only one container and provide handy way to attach to started container."
	echo ""	
	echo "Usage: $script_name (clean | launch | shell | destroy | status | help)"
	echo ""	
	echo "clean   - remove existing docker container, and the image."
	echo "launch  - launch new container."
	echo "shell   - open new interactive terminal in the launched container."
	echo "destroy - destroy the container."
	echo "status  - show information about the container."
	echo "help    - show this help information set."
	echo ""
	echo "Example flow:"
	echo "    $script_name launch"
	echo "    $script_name shell"
	echo "        # just do your work"
	echo "        # Ctrl+D to escape"
	echo "    $script_name destroy"
	echo ""
	echo "During your work you are using only one container."
	echo "You can create as many shells as you want."
	echo "If you exit the shell the container is still running."
	echo ""
}

die() {
	echo >&2 "$script_name: $@"
	exit 1
}


# tutaj zakładamy że każdy kontener stworziny z obrazu abn jest zarządzany przez ten skrypt
# zamiast tego można szukać nadaną nazwę kontenera - container_name
get_all_containers() {
	local result=$(docker container ls -a | grep $container_name | awk '{print $1}')
	[[ $(echo $result | wc -w) < 2 ]] || die "There are more than one container $container_name. Docker is in a vague state. Consider running $script_name clean."
	echo $result
}

get_running_containers() {
	local result=$(docker container ls -f "status=running" | grep $container_name | awk '{print $1}')
	[[ $(echo $result | wc -w) < 2 ]] || die "There are more than one container $container_name. Docker is in a vague state. Consider running $script_name clean."
	echo $result
}

get_images() {
	local result=$(docker image ls -a | grep $image_name | awk '{print $1}')
	[[ $(echo $result | wc -w) < 2 ]] || die "There are more than one image $image_name. Docker is in a vague state. Consider running $script_name clean."
	echo $result
}

main() {
	# input validation and locals set
	[[ "$#" == 1 ]] || ! usage || die "Choose subcommand."
	local subcommand=$1
	local all=$(get_all_containers)
	local running=$(get_running_containers)
	local images=$(get_images)

	case $subcommand in
		clean)
			# container cleaning
			if [[ ! -z $all ]]; then
				if [[ ! -z $running ]]; then
					docker stop $running --time 0 > /dev/null
					[[ $? == 0 ]] || die "Docker container stop failed."
				fi
				docker rm $all > /dev/null
				[[ $? == 0 ]] || die "Docker container remove failed."
				echo "Container cleaned."
			fi
			# image cleaning
			if [[ ! -z $images ]]; then
				docker image rm $images > /dev/null
				[[ $? == 0 ]] || die "Docker image remove failed."
				echo "Image cleaned."
			fi
			echo "Cleaning done."
			;;

		launch)
			# check if container is currently running
			[[ -z $running ]] || die "There is a working container $running. Destroy it first."
			# build a docker image if needed
			if [[ -z $images ]]; then
				docker build -t $image_name .
				[[ $? == 0 ]] || die  "Docker container build failed."
			fi
			# create a container if needed
			if [[ -z $all ]]; then
				## mg
				docker create -t -v $(pwd):$destination_path --name $container_name $image_name > /dev/null
				[[ $? == 0 ]] || die "Docker container create failed."
			fi
			# start stopped or just created container
			docker start $(get_all_containers) > /dev/null
			[[ $? == 0 ]] || die "Docker container start failed."
			echo "Container launched: $(get_running_containers)" 
			;;

		shell)
			# cannot to atach to not running container
			[[ ! -z $running ]] || die "There is no running container here."
			echo ""
			echo "To escape press Ctrl+P Ctrl+Q."
			# open bash in new interactive terminal
			docker exec -it $running /bin/bash
			[[ $? == 0 ]] || die "Docker execution in the container failed."
			;;

		destroy)
			[[ ! -z $running ]] || die "There is no working container here."
			# container cleaning
			if [[ ! -z $all ]]; then
				if [[ ! -z $running ]]; then
					docker stop $running --time 0 > /dev/null
					[[ $? == 0 ]] || die "Docker container stop failed."
				fi
				docker container rm $all
				[[ $? == 0 ]] || die "Docker container remove failed."
				echo "Container destroyed."
			fi
			;;

		status)
			# image information
			if [[ ! -z $images ]]; then
				echo "Available image: $images."
				# container information
				if [[ ! -z $running ]]; then
					echo "Container $running is running."
				else
					if [[ -z $all ]]; then
						echo "There is no container here."
						echo "Consider running '$script_name launch'."
					else
						echo "Container $all is in a vague state."
						echo "Consider running $script_name clear."
					fi
				fi
			else
				echo "There is no available images nor containers."
			fi
			;;

		help)
			help
			;;
	
		*)
			usage
			die "Wrong argument. Check subcommand list."
	esac
}

# main function call
main $@