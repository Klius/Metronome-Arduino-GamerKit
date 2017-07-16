//All display logic goes in this file

//The array where we will combine all the images and render.
byte display[1][8] = {
        {
          B00000000,
          B00000000,
          B00000000,
          B00000000,
          B00000000,
          B00000000,
          B00000000,
          B00000000 
        }
    };
//The bar for separating time_signature
byte bar[1][8] = {
        {
          B00000000,
          B00000000,
          B00000010,
          B00000010,
          B00000011,
          B00000011,
          B00000011,
          B00000000 
        }
    };
    
// Animation for the metronome blips
#define NUMFRAMESIMAGES 4
byte images[NUMFRAMESIMAGES][8] = {
  {
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111  }
  ,

  {
    B00000000,
    B01111110,
    B01111110,
    B01111110,
    B01111110,
    B01111110,
    B01111110,
    B00000000  }
  ,

  {
    B00000000,
    B00000000,
    B00111100,
    B00111100,
    B00111100,
    B00111100,
    B00000000,
    B00000000  }
  ,

  {
    B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00000000,
    B00000000  }
};
byte cls[1][8] = {{
                        B00000000,
                        B00000000,
                        B00000000,
                        B00000000,
                        B00000000,
                        B00000000,
                        B00000000,
                        B00000000 }};
#define SPACESHIPFRAMESIMAGES 5
byte spaceship[SPACESHIPFRAMESIMAGES][8] = {
  {
    B00111100,
    B01000010,
    B00100100,
    B00011000,
    B00000000,
    B00000000,
    B00000000,
    B00000000  },
  {
    B00111100,
    B01000010,
    B00100100,
    B00011000,
    B00100100,
    B00000000,
    B00000000,
    B00000000  },
  {
    B00111100,
    B01000010,
    B00100100,
    B00011000,
    B00100100,
    B01011010,
    B00000000,
    B00000000  },
  {
    B00111100,
    B01000010,
    B00100100,
    B00011000,
    B00100100,
    B01011010,
    B10100101,
    B00000000  },
  {
    B00111100,
    B01000010,
    B00100100,
    B00011000,
    B00100100,
    B01011010,
    B10100101,
    B01011010  }
    
};

/*****
*  Numbers!!!
*****/
#define NUMBERS 10

byte right_numbers[NUMBERS][8] = {
  {
    B00000000,
    B00000000,
    B11000000,
    B11000000,
    B11000000,
    B11000000,
    B11000000,
    B00000000 
  },
  {
    B00000000,
    B00000000,
    B01000000,
    B11000000,
    B01000000,
    B01000000,
    B11000000,
    B00000000 
  },
  {
    B00000000,
    B00000000,
    B11000000,
    B01000000,
    B11000000,
    B10000000,
    B11000000,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B11000000,
    B01000000,
    B11000000,
    B01000000,
    B11000000,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B10000000,
    B10000000,
    B11000000,
    B01000000,
    B01000000,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B11000000,
    B10000000,
    B11000000,
    B01000000,
    B11000000,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B11000000,
    B10000000,
    B11000000,
    B11000000,
    B11000000,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B11000000,
    B01000000,
    B11000000,
    B01000000,
    B01000000,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B11000000,
    B11000000,
    B00000000,
    B11000000,
    B11000000,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B11000000,
    B11000000,
    B11000000,
    B01000000,
    B01000000,
    B00000000 
  } 
};
byte middle_numbers[NUMBERS][8] = {
  {
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00000000 
  },
  {
    B00000000,
    B00000000,
    B00001000,
    B00011000,
    B00001000,
    B00001000,
    B00011000,
    B00000000 
  },
  {
    B00000000,
    B00000000,
    B00011000,
    B00001000,
    B00011000,
    B00010000,
    B00011000,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B00011000,
    B00001000,
    B00011000,
    B00001000,
    B00011000,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B00010000,
    B00010000,
    B00011000,
    B00001000,
    B00001000,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B00011000,
    B00010000,
    B00011000,
    B00001000,
    B00011000,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B00011000,
    B00010000,
    B00011000,
    B00011000,
    B00011000,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B00011000,
    B00001000,
    B00011000,
    B00001000,
    B00001000,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00011000,
    B00011000,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00011000,
    B00001000,
    B00001000,
    B00000000 
  } 
};
byte left_numbers[NUMBERS][8] = {
  {
    B00000000,
    B00000000,
    B00000011,
    B00000011,
    B00000011,
    B00000011,
    B00000011,
    B00000000 
  },
  {
    B00000000,
    B00000000,
    B00000001,
    B00000011,
    B00000001,
    B00000001,
    B00000011,
    B00000000 
  },
  {
    B00000000,
    B00000000,
    B00000011,
    B00000001,
    B00000011,
    B00000010,
    B00000011,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B00000011,
    B00000001,
    B00000011,
    B00000001,
    B00000011,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B00000010,
    B00000010,
    B00000011,
    B00000001,
    B00000001,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B00000011,
    B00000010,
    B00000011,
    B00000001,
    B00000011,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B00000011,
    B00000010,
    B00000011,
    B00000011,
    B00000011,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B00000011,
    B00000001,
    B00000011,
    B00000001,
    B00000001,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B00000011,
    B00000011,
    B00000000,
    B00000011,
    B00000011,
    B00000000 
  }, 
  {
    B00000000,
    B00000000,
    B00000011,
    B00000011,
    B00000011,
    B00000001,
    B00000001,
    B00000000 
  } 
};


