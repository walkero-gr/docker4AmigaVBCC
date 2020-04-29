-include env_make

REPO ?= walkero/docker4amigavbcc
TAG ?= latest-mos
VOLUMES ?= -v "${PWD}/../code":/opt/code
WORKSPACE ?= -w /opt/code
NAME ?= amigavbcc-mos

.PHONY: build buildnc buildlatest shell push pushlatest logs clean release

default: build

build:
	docker build -t $(REPO):$(TAG) .

buildnc:
	docker build --no-cache -t $(REPO):$(TAG) .

buildlatest:
	docker build --no-cache -t $(REPO):latest-mos .

shell:
	docker run -it --rm --name $(NAME) $(VOLUMES) $(WORKSPACE) $(REPO):$(TAG) /bin/bash

push:
	docker push $(REPO):$(TAG)

pushlatest:
	docker push $(REPO):latest-mos

logs:
	docker logs $(NAME)

clean:
	-docker rm -f $(NAME)

release: buildnc push buildlatest pushlatest
