FROM ubuntu

# Workaround https://unix.stackexchange.com/questions/2544/how-to-work-around-release-file-expired-problem-on-a-local-mirror
RUN echo "Acquire::Check-Valid-Until \"false\";\nAcquire::Check-Date \"false\";" | cat > /etc/apt/apt.conf.d/10no--check-valid-until

# install requrire packages
RUN apt-get update && apt-get install -y \
    python3 \
    python3-pip \
    build-essential \
    sudo
RUN pip3 install termcolor

WORKDIR /var/local/abn
CMD bash