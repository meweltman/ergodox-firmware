FROM debian:jessie

RUN apt-get update && apt-get install gcc-avr binutils-avr avr-libc git make vim -y
WORKDIR /

COPY . .

ARG KEYBOARD


WORKDIR /src
RUN KEYBOARD=${KEYBOARD} make
