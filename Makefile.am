# These will be the subdirectories of this directory
SUBDIRS = zzplayer po

# Rule to build RPM distribution package
rpm: $(PACKAGE)-$(VERSION).tar.gz
	cp $(PACKAGE)-$(VERSION).tar.gz /usr/src/redhat/SOURCES
	rpm -ba zzplayer.spec
