DIRS = src

all :
	for d in $(DIRS); do $(MAKE) -C $$d; done

% :
	for d in $(DIRS); do $(MAKE) -C $$d $@; done
