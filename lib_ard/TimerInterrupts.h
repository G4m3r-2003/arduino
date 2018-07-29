#ifndef LIB_ARD_TIMER_INTERRUPTS
#define LIB_ARD_TIMER_INTERRUPTS

/*inizializza il timer 2 abilitando gli interrupt ad una frequenza
  di 1khz. Questa funzione va eseguita nel setup.*/
void initTimer2_2khz();

void initTimer2_1khz();





void initTimer2_2khz()
{
    cli();

    TCCR2A = 0;// set entire TCCR2A register to 0
    TCCR2B = 0;// same for TCCR2B
    TCNT2  = 0;//initialize counter value to 0
    // set compare match register for 2khz increments
    OCR2A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
    // turn on CTC mode
    TCCR2A |= (1 << WGM21);
    // Set CS22 and CS21 bits for prescaler
    TCCR2B |= (1 << CS22) | (0 << CS21);   
    // enable timer compare interrupt
    TIMSK2 |= (1 << OCIE2A);

    sei();
}


void initTimer2_1khz()
{
    cli();

    TCCR2A = 0;// set entire TCCR2A register to 0
    TCCR2B = 0;// same for TCCR2B
    TCNT2  = 0;//initialize counter value to 0
    // set compare match register for 2khz increments
    OCR2A = 249;// = (16*10^6) / (2000*64) - 1 (must be <256)
    // turn on CTC mode
    TCCR2A |= (1 << WGM21);
    // Set CS22 and CS21 bits for prescaler
    TCCR2B |= (1 << CS22) | (0 << CS21);   
    // enable timer compare interrupt
    TIMSK2 |= (1 << OCIE2A);

    sei();
}
#endif