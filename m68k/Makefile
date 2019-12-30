-include env_make

REPO ?= walkero/docker4amigavbcc
TAG ?= 1.0-m68k

.PHONY: build buildnc push release

default: build

build:
	docker build -t $(REPO):$(TAG) .

buildnc:
	docker build --no-cache -t $(REPO):$(TAG) .

push:
	docker push $(REPO):$(TAG)

release: build push
