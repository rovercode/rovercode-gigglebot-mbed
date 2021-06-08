FROM ubuntu:18.04

RUN mkdir /app
WORKDIR /app

RUN apt update && apt install -y \
    python-setuptools \
    python-pip \
    git \
    cmake \
    build-essential \
    ninja-build \
    python-dev \
    libffi-dev \
    libssl-dev \
    srecord \
    gcc-arm-none-eabi

RUN pip install -U pip
RUN pip install yotta
ENTRYPOINT ["yt"]
