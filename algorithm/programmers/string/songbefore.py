from datetime import datetime

def solution(m, musicinfos):
    answer = ''
    note_dict = {'C#': 'H', 'D#': 'I', 'F#': 'J', 'G#': 'K', 'A#': 'L'}
    for key in note_dict:
        m = m.replace(key, note_dict[key])
    candidates = []
    for i, musicinfo in enumerate(musicinfos):
        info = musicinfo.split(',')
        start = datetime.strptime(info[0], '%H:%M')
        end = datetime.strptime(info[1], '%H:%M')
        notes = info[3]
        for key in note_dict:
            notes = notes.replace(key, note_dict[key])
        duration = int((end - start).seconds / 60)
        if len(notes) > duration:
            real_music = notes[:duration]
        else:
            real_music = (notes * (duration // len(notes) + 1))[:duration]
        if m not in real_music:
            continue
        candidates.append((info[2], real_music, duration, i))
    candidates = sorted(candidates, key=lambda x: (x[2], x[3]*-1), reverse=True)
    if not candidates:
        return '(None)'
    answer = candidates[0][0]
    return answer
