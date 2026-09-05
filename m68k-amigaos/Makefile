REPO ?= walkero/docker4amigavbcc
TAG ?= latest-m68k
VOLUMES ?= -v "${PWD}/../code":/opt/code
WORKSPACE ?= -w /opt/code
NAME ?= amigavbcc-m68k

.PHONY: build buildnc build-arm buildnc-arm shell push logs clean test release

default: build

build:
	docker build -t $(REPO):$(TAG) .

buildnc:
	docker build --no-cache -t $(REPO):$(TAG) .

build-arm:
	docker build --platform linux/arm64/v8 --progress plain -t $(REPO):$(TAG) .

buildnc-arm:
	docker build --no-cache --platform linux/arm64/v8 --progress plain -t $(REPO):$(TAG) .


shell:
	docker run -it --rm --name $(NAME) $(VOLUMES) $(WORKSPACE) $(REPO):$(TAG) /bin/bash

push:
	docker push $(REPO):$(TAG)

logs:
	docker logs $(NAME)

clean:
	-docker rm -f $(NAME)

test:
	snyk test --docker $(REPO):$(TAG) --file=Dockerfile

release: buildnc push
