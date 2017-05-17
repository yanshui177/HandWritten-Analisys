/*
IplImage* Integral(IplImage* img, int width, int height)
 {  
    unsigned long *columnSum = new unsigned long[width]; // sum of each column  
    // calculate integral of the first line  
    for(int i=0;i<width;i++)
	{  
        columnSum[i]=inputMatrix[i];  
        outputMatrix[i] = inputMatrix[i];  
        if(i>0)
		{  
            outputMatrix[i] += outputMatrix[i-1];  
        }  
    }  
    for (int i=1;i<height;i++)
	{  
        int offset = i*width;  
        // first column of each line  
        columnSum[0] +=inputMatrix[offset];  
        outputMatrix[offset] = columnSum[0];  
         // other columns   
        for(int j=1;j<width;j++)
		{  
            columnSum[j] += inputMatrix[offset+j];  
            outputMatrix[offset+j] = outputMatrix[offset+j-1] + columnSum[j];   
        }  
    }  
    return 0;  
}  */