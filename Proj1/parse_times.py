import re


def convert_time_secs(time_str : str):
    min, sec = map(float, time_str.split("m"))
    min *=60
    res = min + sec
    res = ",".join(str(res).split("."))
    return res


fh = open("time_tests.txt", "r")
out = open("filtered_realtime.txt", "w")

for line in fh:
    res = re.findall("real\D*(\d.*m\d.*)s", line)
    if (len(res) > 0):
        out.write(convert_time_secs(res[0]) + "\n")
    

fh.close()
out.close()
