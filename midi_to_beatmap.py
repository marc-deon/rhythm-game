#! /usr/bin/env python
import mido

mid = mido.MidiFile('fly me to the star.mid')


beatmap = open('fly me to the star.bm', 'w')

offset = .554
bpm = 124.0
beatmap.write(f"""`
title: Fly Me To The Star
bpm: {bpm}
composer:
vocals:
original:
mapper:
offset: 0
metronome_offset: {offset}
`
""")


notes_used = { }

first = True

elapsed_time = offset
for msg in mid.tracks[0]:
    # second =      tick     * beat/tick            * minute/beat * second/minute
    elapsed_time += msg.time * 1/mid.ticks_per_beat * 1/bpm       * 60.0
    
    # print(msg)
    if msg.type == "note_on":
        if msg.note not in notes_used:
            notes_used[msg.note] = len(notes_used)
        time = int(elapsed_time * 1_000_000)
        if first:
            print("First:", time)
            first = False
        # beatmap.write(f"{notes_used[msg.note]} {time}\n")
        beatmap.write(f"0 {time} {msg.note}\n")
beatmap.close()
print("Notes used:", notes_used)