#include <stdio.h>
#include <stdlib.h>

struct Stack{

	int top ;
	int kapasite;
	int *array;

};

typedef Stack stack;

stack * stackOlustur(int kapasite){

	stack * yeni_stack = (stack*)malloc(sizeof(stack));
	yeni_stack->top = -1; // baslangic indexi -1 yapiyoruz
	yeni_stack->kapasite = kapasite; // uzunluk bilgisi aldık
	yeni_stack->array = (int*)malloc(yeni_stack->kapasite * sizeof(int)); // dizi[kapasite] olusturduk
	return yeni_stack;

}

int stackDoluMu(stack * stack){

	if( stack->top == stack->kapasite -1  )
		return 1;
	return 0;

}

int stackBosMu(stack * stack){

	if( stack->top == -1 )
		return 1;
	return 0;

}

void ekle(stack * stack,int deger){

	if(stackDoluMu(stack)){
		printf("stack dolu\n");
	}else stack->array[++stack->top] = deger;

}

int cikar(stack * stack){

	if(stackBosMu(stack)){
		printf("stack bos\n");
		return -1;
	}else 
		return stack->array[stack->top--];

}

void listele(stack * stack){

	if(stackBosMu(stack)){
		printf("stack bos\n");
	}else{

		for(int i = 0 ; i<stack->top+1;i++){
			printf("%d\n",stack->array[stack->top - i]);
		}
	}
}


int main(){
	

	stack * yeniyigin = stackOlustur(5);

	printf("cikartilan deger: %d\n",cikar(yeniyigin));

	ekle(yeniyigin,2);
	ekle(yeniyigin,5);
	listele(yeniyigin);
	printf("cikartilan deger %d\n",cikar(yeniyigin));
	printf("cikartilan deger %d\n",cikar(yeniyigin));
	printf("cikartilan deger %d\n",cikar(yeniyigin));
	listele(yeniyigin);
	for(int i = 0;i<10;i++){
		ekle(yeniyigin,i*5);
	}
	listele(yeniyigin);


}
