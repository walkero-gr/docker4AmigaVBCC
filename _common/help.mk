
CCRED=\033[31m
CCGREEN=\033[32m
CCYELLOW=\033[33m
CCBLUE=\033[34m
CCPINK=\033[35m
CCLBLUE=\033[36m
CCEND=\033[0m
CCBOLD=\033[1m
CCITAL=\033[3m
CCUNDR=\033[4m


.PHONY: help
help: ## Display this help
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make ${CCLBLUE}<target>${CCEND}\n"} /^[a-zA-Z_0-9-]+:.*?##/ { printf "  ${CCLBLUE}%-15s${CCEND} %s\n", $$1, $$2 } /^##@/ { printf "\n${CCBOLD}%s${CCEND}\n", substr($$0, 5) } ' $(MAKEFILE_LIST)