```
# Voice Broadcast Component Library tts.dll Usage Guide

Z Language Interface Instructions

##### 1.1: Broadcast Settings

| Interface | settts | Set voice broadcast parameters |
|----------|--------|--------------------------------|
| Parameter| volume | Volume level 0~100 |
| Parameter| rate   | Speech rate: 0=normal speed, >0=speed up, <0=slow down |
| Returns  | bool   | Returns true on success, false on failure |
```

bool settts(volume, rate) // Example: settts(90,0) sets 90% volume at normal speed

```
##### 1.2: Text-to-Speech Playback

| Interface | paytts | Convert text to speech |
|----------|--------|------------------------|
| Parameter| data   | Content to broadcast (UTF-8 encoded) |
| Parameter| block  | Blocking flag: 1=returns after completion, 0=returns immediately after starting. Defaults to 0 if omitted |
| Returns  | bool   | Returns true on success, false on failure |
```

bool paytts(data, block/null) // Examples:

// paytts("I am Lei Feng, I like helping others")

// paytts("Playing until completion before returning", 1)

```
##### 1.3: Audio Synthesis

| Interface | swav   | Synthesize fixed-frequency audio |
|----------|--------|----------------------------------|
| Parameter| hz     | Frequency (Hz) |
| Parameter| timeMs | Duration in milliseconds |
| Parameter| volume | Default 90% |
| Returns  | wavbuf | Returns WAV buffer on success, false on failure |
```

c

wavbuf swav(hz, time, volume/null) // Example:

// data = swav(1500, 1000);

// Output audio file using platform file API: outf("1500.wav", data)

```
##### Reference Implementation for C Programs:  
**[Natural Language Understanding NLU - Third-party Function Access](https://gitee.com/kebo521/nlu3)**
```

**Key Translation Notes:**

1. Maintained technical terms consistency (tts.dll, wavbuf, UTF-8)
2. Translated parameter descriptions while keeping programming terms accurate
3. Preserved code examples and comments with English equivalents
4. Converted "Blocking marker" to industry-standard "Blocking flag"
5. Kept function names (settts/paytts/swav) as they're part of the API
6. Translated "voice broadcast" to more technical "Text-to-Speech Playback"
7. Maintained markdown structure for technical documentation clarity
8. Added contextual translation for "雷锋" (Chinese cultural reference)