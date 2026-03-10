
#include <xc.h>

void init_i2c(void)
{
	/* Set SCL and SDA pins as inputs */
	TRISC3 = 1;
	TRISC4 = 1;
	/* Set I2C master mode */
	SSPCON1 = 0x28;

	SSPADD = 0x31;
	/* Use I2C levels, worked also with '0' */
	CKE = 0;
	/* Disable slew rate control  worked also with '0' */
	SMP = 1;
	/* Clear SSPIF interrupt flag */
	SSPIF = 0;
	/* Clear bus collision flag */
	BCLIF = 0;
}

void i2c_idle(void)
{
    /*0- instruction completed
     1- instruction not completed
     */
	while (!SSPIF);
	SSPIF = 0;
}

void i2c_ack(void)
{
    /* not using */
	if (ACKSTAT)
	{
		/* Do debug print here if required */
	}
}

void i2c_start(void)
{
    /* 
     used to start communication 
     * to start set SEN = 1
     * SEN is instruction so calling i2c_idle() to check 
     */
	SEN = 1;
	i2c_idle();
}

void i2c_stop(void)
{
    /* 
     to stop communication 
     PEN to intiate the stop condition 
     */
	PEN = 1;
	i2c_idle();
}

void i2c_rep_start(void)
{
    /* repeat start 
     */
	RSEN = 1;
	i2c_idle();
}

void i2c_write(unsigned char data)
{
    /*
     to transmit 1 byte of data
     data is stored into SSPBUF
     */
	SSPBUF = data;
	i2c_idle();
}

void i2c_rx_mode(void)
{
    /* 
     to put mc on receive mode*/
	RCEN = 1;
	i2c_idle();
}

void i2c_no_ack(void)
{
    /*
     to inform no ack by sending 1 ( ack 0)
     */
	ACKDT = 1;
	ACKEN = 1;
}

unsigned char i2c_read(void)
{
    /*
     to recive data from slave 
     after that can read data from SSPBUF */
	i2c_rx_mode();   // recive mode
	i2c_no_ack();   //no ack

	return SSPBUF;
}