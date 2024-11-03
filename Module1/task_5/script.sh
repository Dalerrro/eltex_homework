#/bin/bash

ps aux

echo -e "\n Enter string:"
read STR

pids=$(ps aux | grep "$STR" | grep -v "grep" | awk '{print $2}')

if [ -z "$pids" ]; then
    echo "process not found"
else
    echo "killing pid: $pids"
    echo "$pids" | xargs kill -9
fi