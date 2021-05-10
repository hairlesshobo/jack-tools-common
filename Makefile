GL_GIT=git@gitlab.com:rd--/r-common.git
GL_HTTP=https://gitlab.com/rd--/r-common.git

all:
	echo "r-common"

clean:
	(cd c ; make clean)

push-gl:
	git push $(GL_GIT)

push-gl-tags:
	git push $(GH_GIT) --tag

pull-gl:
	git pull $(GL_HTTP)

update-rd:
	ssh rd@rohandrape.net "(cd sw/r-common ; git pull $(GL_HTTP))"

push-all:
	make push-gl update-rd
