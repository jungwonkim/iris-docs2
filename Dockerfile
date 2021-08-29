FROM ubuntu:18.04

RUN apt-get update &&\
    apt-get install -y build-essential &&\
    apt-get install -y git cmake vim
