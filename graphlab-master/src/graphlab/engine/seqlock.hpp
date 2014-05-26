#include <sched.h>

class seqlock {
private:
        volatile uint64_t sequence;

public:
        seqlock()
        {
                sequence = 0;
        }

        void lock()
        {
                __sync_fetch_and_add(&sequence, 1);
        }

        void unlock()
        {
                __sync_fetch_and_add(&sequence, 1);
        }

        uint64_t begin()
        {
                uint64_t seq = sequence;
                while (seq & 1)
                {
                        sched_yield();
                        seq = sequence;
                }
                return seq;
        }

        uint64_t finish(uint64_t seq)
        {
                return seq == sequence;
        }
};
