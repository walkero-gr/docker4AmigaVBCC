#!/usr/bin/bash

echo -e "${CCPINK}${CCBOLD}\n---> Create amidev user ${CCEND}"

# Remove any existing users with this UID first
existing_user=$(getent passwd "$AMIDEV_USER_ID" | cut -d: -f1);
if [[ -n "$existing_user" ]]; then 
	deluser "$existing_user"
fi

# Then remove any existing group with this GID
existing_group=$(getent group "$AMIDEV_GROUP_ID" | cut -d: -f1);
if [[ -n "$existing_group" ]]; then 
	delgroup "$existing_group"
fi

addgroup --gid $AMIDEV_GROUP_ID amidev
adduser --uid $AMIDEV_USER_ID \
	--disabled-password \
	--shell /bin/bash \
	--gid $AMIDEV_GROUP_ID \
	--home /home/amidev amidev

sed -i '/^amidev/s/!/*/' /etc/shadow; 

BASHFILE=/home/amidev/.bashrc

cp ~/.bashrc /home/amidev/
chown amidev:amidev $BASHFILE

sed -i '4c\'"\nparse_git_branch() {\n\
git branch 2> /dev/null | sed -e \'/^[^*]/d\' -e \'s/* \\\(.*\\\)/ (\\\1)/\'\n\
}\n" $BASHFILE

sed -i '43c\'"force_color_prompt=yes" $BASHFILE

sed -i '57c\'"    PS1=\'\${debian_chroot:+(\$debian_chroot)}\\\[\\\033[01;32m\\\]\\\u@\\\h\\\[\\\033[00m\\\]:\\\[\\\033[01;34m\\\]\\\w\\\[\\\033[01;31m\\\]\$(parse_git_branch)\\\[\\\033[00m\\\]\\\$ '" $BASHFILE

sed -i '59c\'"    PS1=\'\${debian_chroot:+(\$debian_chroot)}\\\u@\\\h:\\\w \$(parse_git_branch)\$ \'" $BASHFILE

sed -i '3c\'"\nexport PATH=${PATH}\n" $BASHFILE