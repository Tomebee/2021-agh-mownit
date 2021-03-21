FROM ubuntu:20.04 AS base
RUN apt-get update
RUN apt-get -y install build-essential
RUN apt-get -y install libgsl-dev
RUN DEBIAN_FRONTEND=noninteractive apt-get -y --fix-missing install gnuplot

FROM base AS run
RUN mkdir lab
WORKDIR /lab2
EXPOSE 80
RUN ["/bin/bash"]