#include <stdio.h>
#define SIZE 5

// Submission Queue
int SQ[SIZE];
int sq_head = 0;
int sq_tail = 0;

// Completion Queue
int CQ[SIZE];
int cq_head = 0;
int cq_tail = 0;

// Check full/empty
int is_full(int head, int tail) {
    return ((tail + 1) % SIZE) == head;
}

int is_empty(int head, int tail) {
    return head == tail;
}

// Add to Submission Queue
void submit(int data) {
    if (is_full(sq_head, sq_tail)) {
        printf("SQ Full\n");
        return;
    }
    SQ[sq_tail] = data;
    sq_tail = (sq_tail + 1) % SIZE;
}

// Process SQ → CQ
void process() {
    if (is_empty(sq_head, sq_tail)) {
        printf("SQ Empty\n");
        return;
    }

    int data = SQ[sq_head];
    sq_head = (sq_head + 1) % SIZE;

    // Simulate processing (e.g., multiply by 2)
    int result = data * 2;

    if (is_full(cq_head, cq_tail)) {
        printf("CQ Full\n");
        return;
    }

    CQ[cq_tail] = result;
    cq_tail = (cq_tail + 1) % SIZE;
}

// Read from Completion Queue
void complete() {
    if (is_empty(cq_head, cq_tail)) {
        printf("CQ Empty\n");
        return;
    }

    int result = CQ[cq_head];
    cq_head = (cq_head + 1) % SIZE;

    printf("Completed Data: %d\n", result);
}

int main() {
    submit(10);
    submit(20);

    process();   // move to CQ
    process();

    complete();  // print after completion
    complete();

    return 0;
}
