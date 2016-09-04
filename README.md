# MIDI-Makey-Makey

## Concept

Turn Makey Makey into MIDI Controller.

Mod the Makey Makey firmware so that it sends MIDI Note signals instead of keyboard keys signals.  
Use JSFX Effects to map this signal inside a DAW or VST Host without re-changing the Makey Makey firmware.

## Pack Content

### Core Files

- Makey Makey MIDI Firmware mod (better for JSFX integration)
- JSFX Effects for MIDI Routing inside a DAW or VST Host.

### Extra Files

These files are hosted here for convenience.

- Makey Makey MIDI Firmware original, by MineMooder (for reference)

## Installation

### Firmware and Data Serialization

Follow MineMooder Instructables Tutorial [Makey Makey MIDI controller](http://www.instructables.com/id/Makey-Makey-MIDI-controller/), but use the **X-Raym_Makey-Makey-midicontroller_mod.ino** firmware from this repo instead of the one from the tutorial.

### JSFX

Cockos JSFX effects are effects in a script format, which allow quick development and maintenance.

Cockos'DAW [REAPER](http://www.reaper.fm) handle them natively, but they can be embeded in other DAW or VST host for free with Cockos [ReaPlugs ReaJS](http://reaper.fm/reaplugs/) VST plugin.

#### REAPER

You can import the JSFX with [ReaPack](http://www.reapack.com/).

1. Install ReaPack
1. Copy the URL `https://raw.githubusercontent.com/X-Raym/MIDI-Makey-Makey/master/index.xml`
1. Open REAPER
1. *Extension* Menu > *ReaPack* > *Import Repository* > Paste the URL
1. Synchronize Package
1. JSFX should be avaible in your FX list!

#### Other DAW and VST Host

1. Download Install ReaPlugs ReaJS
1. Download JSFX from this repo
1. Open ReaJS in your VST Host
1. Import JSFX
1. Enjoy!

## Notes

Other JSFX, included in REAPER or from online repositories, can be especially useful for Makey Makey MIDI workflow:

- *Fixed MIDI Note Length* (native), prevent too close notes to be sent. Useful to avoid indesired quick note repetions.
- *X-Raym_MIDI Note to CC* (from [X-Raym's REAPER-ReaScripts repo](https://github.com/X-Raym/REAPER-ReaScripts)), can help you map a MIDI Note to a MIDI CC event.

## Backup

If you want to restore Makey Makey default firmware, use the [Sparkfun firmware](https://github.com/sparkfun/MaKeyMaKey/tree/master/firmware/Arduino/makey_makey).

## Donation

You can support this project on my [website](http://www.extremraym.com/en/donation). Thanks!
