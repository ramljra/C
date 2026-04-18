#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 5
#define NUM_QUEUES 2

typedef struct {
    int data[SIZE];
    int head;
    int tail;
    pthread_mutex_t lock;
} Queue;

// SQ and CQ arrays
Queue SQ[NUM_QUEUES];
Queue CQ[NUM_QUEUES];

// Queue helpers
int is_full(Queue *q) {
    return ((q->tail + 1) % SIZE) == q->head;
}

int is_empty(Queue *q) {
    return q->head == q->tail;
}

// Submit to SQ
void submit(int qid, int value) {
    Queue *q = &SQ[qid];

    pthread_mutex_lock(&q->lock);

    if (is_full(q)) {
        printf("SQ%d Full\n", qid);
    } else {
        q->data[q->tail] = value;
        q->tail = (q->tail + 1) % SIZE;
        printf("Submitted %d to SQ%d\n", value, qid);
    }

    pthread_mutex_unlock(&q->lock);
}

// Process thread (simulate controller)
void* process_queue(void *arg) {
    int qid = *(int*)arg;

    while (1) {
        Queue *sq = &SQ[qid];
        Queue *cq = &CQ[qid];

        pthread_mutex_lock(&sq->lock);

        if (!is_empty(sq)) {
            int data = sq->data[sq->head];
            sq->head = (sq->head + 1) % SIZE;

            pthread_mutex_unlock(&sq->lock);

            // Simulate processing delay
            usleep(500000);

            int result = data * 10;

            pthread_mutex_lock(&cq->lock);

            if (!is_full(cq)) {
                cq->data[cq->tail] = result;
                cq->tail = (cq->tail + 1) % SIZE;
                printf("Processed %d -> %d in Q%d\n", data, result, qid);
            }

            pthread_mutex_unlock(&cq->lock);
        } else {
            pthread_mutex_unlock(&sq->lock);
            usleep(100000);
        }
    }
}

// Read completion
void complete(int qid) {
    Queue *cq = &CQ[qid];

    pthread_mutex_lock(&cq->lock);

    if (!is_empty(cq)) {
        int result = cq->data[cq->head];
        cq->head = (cq->head + 1) % SIZE;
        printf("CQ%d Output: %d\n", qid, result);
    }

    pthread_mutex_unlock(&cq->lock);
}

// Init queues
void init() {
    for (int i = 0; i < NUM_QUEUES; i++) {
        SQ[i].head = SQ[i].tail = 0;
        CQ[i].head = CQ[i].tail = 0;
        pthread_mutex_init(&SQ[i].lock, NULL);
        pthread_mutex_init(&CQ[i].lock, NULL);
    }
}

int main() {
    pthread_t threads[NUM_QUEUES];
    int ids[NUM_QUEUES];

    init();

    // Create processing threads
    for (int i = 0; i < NUM_QUEUES; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, process_queue, &ids[i]);
    }

    // Submit data
    submit(0, 10);
    submit(1, 20);
    submit(0, 30);
    submit(1, 40);

    sleep(2);

    // Read completions
    complete(0);
    complete(1);
    complete(0);
    complete(1);

    return 0;
}
