from mido import MidiFile

mid = MidiFile('Yankee Doodle.mid')
file = open("data.txt", "w")
min=100
max=0

for i, track in enumerate(mid.tracks):
    for msg in track:
        if str(msg)[:4]=="note":
            file.write(str(msg))
            file.write("\n")
            temp=str(msg).index("note=")
            note=int(str(msg)[temp+5:temp+7])
            if min>note:
                min=note
            if max<note:
                max=note
file.close()
print(max, min, max-min)