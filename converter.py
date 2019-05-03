
from pydub import AudioSegment
from pysndfx.dsp import AudioEffectsChain

fx = (
     AudioEffectsChain()
     .reverb()
     .phaser()
     )

songName = input("name of song: ")
out = "text.ogg"

def converter(inName):

    song = AudioSegment.from_wav(inName).split_to_mono()
    
    faded1 = song[0].fade(to_gain=0, start=0, duration=3100)
    faded2 = song[1].fade(to_gain=0, start=0, duration=1000)
    
    fadedL = faded1;
    
    fadedr = faded2.fade(to_gain=-12, start=1000, duration=600)
    fadedR = fadedr.fade(to_gain=0, start=1600, duration=1500)
    
    st=3100
    gain=-4
    n=1
    
    while st < len(song[0]):
        fadedL = fadedL.fade(to_gain=(gain), start=st, duration=600) 
        if n%3 == 0:
            fadedL = fadedL.fade(to_gain=0, start=st+600, duration=1500)
            st+=2100
            gain*=-1
        else:
            st+=600
        n+=1
        
    st=3100
    gain=4
    n=1
    
    while st < len(song[0]):
        fadedR = fadedR.fade(to_gain=(gain), start=st, duration=600) 
        if n%3 == 0:
            fadedR = fadedR.fade(to_gain=0, start=st+600, duration=1500)
            st+=2100
            gain*=-1
        else:
            st+=600
        n+=1
    
    stereo_sound = AudioSegment.from_mono_audiosegments(fadedL, fadedR)
    fx(stereo_sound, out)
    out.export("reverbAudio.wav", format="wav")
    
converter(songName)