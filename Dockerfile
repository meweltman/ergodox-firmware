FROM debian:jessie

RUN apt-get update && apt-get install gcc-avr binutils-avr avr-libc git make vim -y
RUN git clone 'http://github.com/mweltman/ergodox-firmware'
