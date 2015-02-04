# LM19
LM19 code


	temp = (unsigned int)ADC_convert();
	temp = temp * 3.0f / 1024.0f;
	temp =  -1481.96 + sqrt(2.1962 + (1.8639 - temp) / 3.88) * 1000 + 0.5;
http://i.gyazo.com/b773980b551094d045ddda298329c151.png
