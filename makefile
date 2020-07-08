# -----------------------------------------------------------------------------
# makefile for the ergoDOX project
#
# This should produce a single file (probably in an archive format) for
# distribution, containing everything people will need to use the software.
#
# DEPENDENCIES:  This is unabashedly dependant on (the GNU implementation of)
# various Unix commands, and therefore probably won't work in a Windows
# environment (besides maybe cygwin).  Sorry...  I don't know a good portable
# way to write it.
#
# TODO:
# - include doc files (and maybe render them in html)
# - include the UI stuff (once it's done)
# -----------------------------------------------------------------------------
# Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
# Released under The MIT License (MIT) (see "license.md")
# Project located at <https://github.com/benblazak/ergodox-firmware>
# -----------------------------------------------------------------------------


include src/makefile-options

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------

.PHONY: build

manuform:
	docker build -t ergodox-firmware --build-arg KEYBOARD=manuform .
	docker create -ti --name helper ergodox-firmware bash
	docker cp helper:/src/manuform.hex ${PWD}/manuform.hex
	docker rm helper

dactyl:
	docker build -t ergodox-firmware --build-arg KEYBOARD=dactyl .
	docker create -ti --name helper ergodox-firmware bash
	docker cp helper:/src/dactyl.hex ${PWD}/dactyl.hex
	docker rm helper
