#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t
#include <stdio.h> // for printf

uint32_t my_ntohl(uint32_t n){
	uint32_t hl;
	uint32_t hl1 = (n & 0xFF000000) >> 24;
	uint32_t hl2 = (n & 0x00FF0000) >> 8;
	uint32_t hl3 = (n & 0x0000ff00) << 8;
	uint32_t hl4 = (n & 0x000000FF) << 24;
	hl=hl1|hl2|hl3|hl4;
	return hl;
}


void add_nbo(uint8_t buf1[], uint8_t buf2[]) {
    uint32_t* p1 = (uint32_t*)(buf1);
    uint32_t n1 = my_ntohl(*p1);
    uint32_t* p2 = (uint32_t*)(buf2);
    uint32_t n2 = my_ntohl(*p2);
    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n",n1, n1, n2, n2, n1+n2, n1+n2);
}


int main(int argc, char *argv[]) {
    
    uint8_t buf1[4], buf2[4]; 
    FILE *f1, *f2;
    f1 = fopen(argv[1], "rb"); 
    f2 = fopen(argv[2], "rb");
    
    if(!f1 || !f2){
    printf("file open error.\n");
        return 1;
    }
    
    if(fread(buf1, 1, 4, f1) != 4 || fread(buf2, 1, 4, f2) != 4){
        printf("file read error.\n");     
        return 1;
    }    

    add_nbo(buf1, buf2);
    
    fclose(f1); fclose(f2);
    return 0;
}
