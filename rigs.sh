#!/bin/sh

OS=$(uname)
CURRENT_DIR=$(pwd)
RIGS=$((RIGS))
while [ $RIGS -gt 0 ]; do
  if [ $OS = "Darwin" ]; then
  #osascript -e 'tell application "Terminal" to tell window 1 to do script "./rig.sh" in selected tab'
  #osascript -e 'tell application "Terminal" to activate' -e 'tell application "System Events" to keystroke "t" using command down' -e 'tell application "Terminal" to do script "./rig.sh" in front window'
  #osascript -e 'tell application "Terminal" to do script "cd \"'$CURRENT_DIR'\"; ./rig.sh"'
    osascript -e 'tell application "Terminal" to do script "cd '$CURRENT_DIR'; ./rig.sh"'
  fi
  RIGS=$((RIGS - 1))
done

echo "repeaters spawned"
