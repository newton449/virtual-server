mechineVersion=$(uname -m)
if [ "$mechineVersion" == "x86_64" ]; then
	echo "x64"
else
	echo "x86"
fi

