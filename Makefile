GL_GIT=git@gitlab.com:rd--/r-common.git
GL_HTTP=https://gitlab.com/rd--/r-common.git

all:
	echo "r-common"

clean:
	(cd c ; make clean)

push-gl:
	git push $(GL_GIT)

pull-gl:
	git pull $(GL_HTTP)

push-tags:
	git push $(GL_GIT) --tags

update-rd:
	ssh rd@rohandrape.net "(cd sw/r-common ; git pull $(GL_HTTP))"

push-all:
	make push-gl update-rd
