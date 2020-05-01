FROM debian:jessie

RUN apt-get update && apt-get install gcc-avr binutils-avr avr-libc git make vim -y
WORKDIR /

COPY . .

WORKDIR /src
RUN make
