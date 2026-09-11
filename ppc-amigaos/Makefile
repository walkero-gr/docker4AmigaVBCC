include ../_common/help.mk

# Target architecture for the build
ARCH=ppc-amigaos

# Release version
REL?=2.0.0

REPO=walkero/docker4amigavbcc
TAG=$(ARCH)-$(REL)
VOLUMES=-v "${PWD}/../code":/opt/code
WORKSPACE=-w /opt/code
NAME=amigavbcc-$(TAG)

#####################################################################
##@ Build dev environment

.PHONY: build
build: ## Build the main dev environment image
	docker build --progress plain -t $(REPO):$(TAG) .

.PHONY: buildnc
buildnc: ## Build the main dev environment image with no-cache
	docker build --progress plain --no-cache -t $(REPO):$(TAG) .

.PHONY: shell
shell: ## Create a container with the latest Docker image and use it
	docker run -it --rm --name $(NAME) $(VOLUMES) $(WORKSPACE) $(REPO):$(TAG) /bin/bash

#####################################################################
##@ Helpers

.PHONY: push
push: ## Push the Docker image to the repository
	docker push $(REPO):$(TAG)

.PHONY: logs
logs: ## Show the logs of the container
	docker logs $(NAME)

.PHONY: clean
clean: ## Remove the container if it exists
	-docker rm -f $(NAME)

.PHONY: test
test: ## Test the Docker image with snyk
	snyk test --docker $(REPO):$(TAG) --file=Dockerfile

.PHONY: release
release: buildnc push ## Build and push the Docker image
