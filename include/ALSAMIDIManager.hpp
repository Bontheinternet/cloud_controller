#pragma once
#include <alsa/asoundlib.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <functional>

class ALSAMIDIManager {
public:
    using NoteCallback = std::function<void(uint8_t channel, uint8_t note, uint8_t velocity, bool is_on)>;
    using CCallback    = std::function<void(uint8_t channel, uint8_t cc, uint8_t value)>;

    ALSAMIDIManager() : seq_handle(nullptr), running(false), port_id(-1) {}
    ~ALSAMIDIManager() { stop(); }

    bool init() {
        int err = snd_seq_open(&seq_handle, "default", SND_SEQ_OPEN_INPUT, 0);
        if (err < 0) return false;

        snd_seq_set_client_name(seq_handle, "CloudController_MIDI");
        port_id = snd_seq_alloc_simple_port(
            seq_handle, "MIDI Input Port",
            SND_SEQ_PORT_CAP_WRITE | SND_SEQ_PORT_CAP_SUBS_WRITE,
            SND_SEQ_PORT_TYPE_MIDI_GENERIC | SND_SEQ_PORT_TYPE_APPLICATION
        );
        return (port_id >= 0);
    }

    void start(NoteCallback note_cb, CCallback cc_cb) {
        if (!seq_handle || running) return;
        note_callback = note_cb;
        cc_callback = cc_cb;
        running = true;
        midi_thread = std::thread(&ALSAMIDIManager::polling_loop, this);
    }

    void stop() {
        running = false;
        if (seq_handle) {
            snd_seq_close(seq_handle);
            seq_handle = nullptr;
        }
        if (midi_thread.joinable()) midi_thread.join();
    }

private:
    snd_seq_t* seq_handle;
    int port_id;
    std::atomic<bool> running;
    std::thread midi_thread;
    NoteCallback note_callback;
    CCallback cc_callback;

    void polling_loop() {
        while (running && seq_handle) {
            snd_seq_event_t* ev = nullptr;
            if (snd_seq_event_input(seq_handle, &ev) < 0) continue;
            if (ev) {
                uint8_t ch = ev->data.control.channel;
                if (ev->type == SND_SEQ_EVENT_NOTEON && note_callback) {
                    note_callback(ch, ev->data.note.note, ev->data.note.velocity, ev->data.note.velocity > 0);
                } else if (ev->type == SND_SEQ_EVENT_NOTEOFF && note_callback) {
                    note_callback(ch, ev->data.note.note, 0, false);
                } else if (ev->type == SND_SEQ_EVENT_CONTROLLER && cc_callback) {
                    cc_callback(ch, ev->data.control.param, ev->data.control.value);
                }
                snd_seq_free_event(ev);
            }
        }
    }
};