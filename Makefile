all:
	echo "r-common"

clean:
	(cd c ; make clean)

push-all:
	git push git@gitlab.com:rd--/r-common.git
	ssh rd@rohandrape.net "(cd sw/r-common ; git pull https://gitlab.com/rd--/r-common.git)"

push-tags:
	git push git@gitlab.com:rd--/r-common.git --tags
