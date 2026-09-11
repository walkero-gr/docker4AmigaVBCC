pipeline {
	agent any
	environment {
		DOCKERHUB_CREDS=credentials('walkero-dockerhub')
		DOCKERHUB_REPO="walkero/docker4amigavbcc"
	}
	stages {
		stage('ppc-amigaos') {
			when { buildingTag() }
			stages {
				stage('build-images') {
					environment {
						TAG_VERSION = "${TAG_NAME.replace('v', '')}"
					}
					matrix {
						axes {
							axis {
								name 'ARCH'
								values 'amd64', 'arm64'
							}
							axis {
								name 'SYSTEM'
								values 'ppc-morphos', 'ppc-amigaos', 'm68k-amigaos'
							}
						}
						agent { label "agent-${ARCH}" }
						stages {
							stage('build-${SYSTEM}') {
								options {
									timeout(time: 60, unit: 'MINUTES')
								}
								steps {
									script {
										buildAndPush(SYSTEM, ARCH)
									}
								}
							}
						}
						post {
							always {
								sh """
									docker logout
								"""
							}
						}
					}
				}
				stage('create-manifests') {
					environment {
						TAG_VERSION = "${TAG_NAME.replace('v', '')}"
					}
					matrix {
						axes {
							axis {
								name 'SYSTEM'
								values 'ppc-morphos', 'ppc-amigaos', 'm68k-amigaos'
							}
						}
						agent { label "agent-amd64" }
						stages {
							stage('build-${SYSTEM}-manifest') {
								steps {
									script {
										createAndPushManifests('os4')
									}
								}
							}
						}
					}
				}

			}
		}
	}
}

def buildAndPush(system, arch) {
	def imageTagBase = "${env.DOCKERHUB_REPO}:${system}"
	def imageTagVersioned = "${imageTagBase}-${env.TAG_VERSION}-${arch}"
	def imageTagLatest = "${imageTagBase}-${arch}"

	try {
		sh """
			cd ${system}
			docker buildx build \
				--provenance=false \
				--cache-from ${imageTagLatest} \
				-t ${imageTagVersioned} \
				-t ${imageTagLatest} \
				-f Dockerfile .
		"""
		retry(3) {
			sh """
				echo \$DOCKERHUB_CREDS_PSW | docker login -u \$DOCKERHUB_CREDS_USR --password-stdin
				docker push ${imageTagVersioned}
				docker push ${imageTagLatest}
			"""
		}
	} finally {
		sh 'docker logout'
	}
}

def createAndPushManifests(system) {
	def imageTagBase = "${env.DOCKERHUB_REPO}:${system}-gcc${gccVer}"
	def imageTagVersioned = "${imageTagBase}-${env.TAG_VERSION}"
	def imageTagLatest = imageTagBase

	sh """
		docker manifest rm ${imageTagVersioned} || true
		docker manifest rm ${imageTagLatest} || true

		docker manifest create \
			--amend ${imageTagVersioned} \
			${imageTagVersioned}-amd64 \
			${imageTagVersioned}-arm64

		docker manifest create \
			--amend ${imageTagLatest} \
			${imageTagLatest}-amd64 \
			${imageTagLatest}-arm64
	"""


	try {
		sh 'echo \$DOCKERHUB_CREDS_PSW | docker login -u \$DOCKERHUB_CREDS_USR --password-stdin'
		gccVersions.each { gccVer ->
			def imageTagBase = "${env.DOCKERHUB_REPO}:${system}-gcc${gccVer}"
			def imageTagVersioned = "${imageTagBase}-${env.TAG_VERSION}"
			def imageTagLatest = imageTagBase

			retry(3) {
				sh """
					docker manifest push ${imageTagVersioned}
					docker manifest push ${imageTagLatest}
				"""
			}
		}
	} finally {
		sh 'docker logout'
	}
}
