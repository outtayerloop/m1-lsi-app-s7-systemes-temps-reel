void do_work( unsigned int duration);

int main(int argc, char** argv) {
    do_work(1000);
    return 0;
}

void do_work( unsigned int duration){
    int i;
    for(i = 0; i<duration; ++i)
        asm volatile ("nop");
}


