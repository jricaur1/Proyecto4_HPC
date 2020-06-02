int mod = 0;
float[][] prediction(){
    float aum = 0.1;
    float pd[14][4];
    for(int i = 0; i < pd.length(); ++i){
        for(int j = 0; j < pd[i].length(); ++j){
            pd[i][j] = aum;
            aum += 0.1;
        }
    }
    return pd;
}

float[][] slidingWindow(float[][] matrix){
    float sw[7][4];

    for(int i = 0 + mod; i < 7 + mod; ++i){
        for(int j = 0; j < 4; ++j){
            sw[i][j] = matrix[i][j];
        }
    }
    ++mod;
    return sw;
}