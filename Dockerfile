# Use an official Ubuntu as a parent image
FROM ubuntu:20.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=C.UTF-8

# Install dependencies
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    libssl-dev \
    zlib1g-dev \
    libboost-all-dev \
    libjsoncpp-dev \
    uuid-dev \
    libsqlite3-dev \
    && rm -rf /var/lib/apt/lists/*

# Clone Drogon source code and install it
RUN git clone https://github.com/drogonframework/drogon /drogon && \
    cd /drogon && \
    git submodule update --init && \
    mkdir build && cd build && \
    cmake .. && make && make install

# Set the working directory
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app 

COPY deploy.sh ./deploy.sh 
RUN chmod +x ./deploy.sh

# Run the application on container startup
CMD sh ./deploy.sh && tail -f /dev/null
