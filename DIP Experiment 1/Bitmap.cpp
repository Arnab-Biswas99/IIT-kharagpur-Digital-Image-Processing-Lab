#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <iostream>
#include<algorithm>
#include <fstream>
#include <cstring>
#include <cstdint>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
struct bmpheader{
	unsigned char name0; 
	unsigned char name1;
	unsigned int size;
	unsigned int temp;
	unsigned int image_offset;
};
struct infohead{
	unsigned int header_size;
	unsigned int width;
	unsigned int height;
	unsigned short int colorplanes;
	unsigned short int bitsperpixel;
	unsigned int compression;
	unsigned int image_size;
	unsigned int temp[4];
};

struct RGB{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char waste;
};
struct Image{
	int height;
	int width;
	struct RGB **rgb;
};

struct Image newimage(FILE *fp,int height,int width){
	struct Image pic;												
	int i;
	pic.rgb=(struct RBG**)malloc(height*sizeof(void*));
	pic.height=height;
	pic.width=width;
	for(i=height-1;i>=0;i--){
		pic.rgb[i]=(struct RGB*)malloc(width*sizeof(struct RGB));
		fread(pic.rgb[i],width,sizeof(struct RGB),fp);
	return pic;
}

struct Image scaledimage(int height,int width,struct Image image,int scale){
	struct Image pic;
	int i,j=0;
	pic.rgb=(struct RBG**)malloc(height*sizeof(void*));
	pic.height=height;
	pic.width=width;
	for(i=height-1;i>=0;i--){
		pic.rgb[i]=(struct RGB*)malloc(width*sizeof(struct RGB));
	}
	for(i=0;i<pic.height;i++){
		for(j=0;j<pic.width;j++)
		{
			if(i%scale==0&&j%scale==0) 
			pic.rgb[i][j]=image.rgb[i/scale][j/scale];
			else
			pic.rgb[i][j].red=pic.rgb[i][j].blue=pic.rgb[i][j].green=0;
		}
	}
	return pic;
}

void scaled_image(struct Image pic,int scale){
	int i,j;																			
	unsigned char T;
	struct RGB PT;
	for(i=0;i<pic.height;i++)
		for(j=0;j<pic.width;j++)
		{
			if(j%scale!=0)
			pic.rgb[i][j]=pic.rgb[i][j-1];
			if(i%scale!=0)
			pic.rgb[i][j]=pic.rgb[i-1][j];
		}
}

int scaled(struct bmpheader header2, struct infohead dibheader2, struct Image pic,int scale){
	
	int i;
	FILE *fpw=fopen("Upscaled.bmp","wb");
	if (fpw==NULL) return 1;
	
	scaled_image(pic,scale);
	fwrite(&header2.name0,1,1,fpw);
	fwrite(&header2.name1,1,1,fpw);
	fwrite(&header2.size,3*sizeof(int),1,fpw);

	fwrite(&dibheader2,sizeof(struct infohead),1,fpw);
	fseek(fpw,header2.image_offset,SEEK_SET);
	for(i=pic.height-1;i>=0;i--){
		fwrite(pic.rgb[i],pic.width,sizeof(struct RGB),fpw);
	}
	fclose(fpw);
	return 0;
		
}

struct Image createimage(int height,int width){
	struct Image pic;
	int i,j=0;
	pic.rgb=(struct RBG**)malloc(height*sizeof(void*));
	pic.height=height;
	pic.width=width;
	
	for(i=height-1;i>=0;i--){
		pic.rgb[i]=(struct RGB*)malloc(width*sizeof(struct RGB));
	}
	for(i=0;i<pic.height;i++){
		for(j=0;j<pic.width;j++)
		{
			pic.rgb[i][j].red=pic.rgb[i][j].blue=pic.rgb[i][j].green=250;
		}
	}
	return pic;
}
void rotation45(struct Image pic,struct Image image){
	int x,y,x1,y1;																			
	unsigned char T;
	struct RGB PT;
	for(y=(-pic.height/4-1)+1;y<(pic.height/4)-1;y++)
		for(x=(-pic.width/4)+1;x<pic.width/4-1-1;x++)
		{
			y1=pic.height/2-1+ (-(x+pic.width/4-pic.height/4+1+y)/sqrt(2.0));
			x1=pic.width/2+ ((pic.width/4+x-y-pic.height/4+1)/sqrt(2.0));														
			pic.rgb[y1][x1]=image.rgb[pic.height/4-1-y][pic.width/4+x];
		}
}

int rotate45(struct bmpheader header2, struct infohead dibheader2, struct Image pic,struct Image image){
	int i;
	FILE *fpw=fopen("Rotated.bmp","wb");
	if (fpw==NULL) return 1;
	rotation45(pic,image);
	fwrite(&header2.name0,1,1,fpw);
	fwrite(&header2.name1,1,1,fpw);
	fwrite(&header2.size,3*sizeof(int),1,fpw);
	fwrite(&dibheader2,sizeof(struct infohead),1,fpw);
	fseek(fpw,header2.image_offset,SEEK_SET);
	for(i=pic.height-1;i>=0;i--){
		fwrite(pic.rgb[i],pic.width,sizeof(struct RGB),fpw);
	}
	fclose(fpw);
	return 0;	
}

void freeImage(struct Image pic){
	int i;
	for(i=pic.height-1;i>=0;i--){
		free(pic.rgb[i]);
	}
	free(pic.rgb);
}

unsigned char grayscale(struct RGB rgb){
	return ((0.3*rgb.red)+(0.6*rgb.green)+(0.1*rgb.blue));
}

void RGBImageToGrayscale(struct Image pic){
	int i,j;																										
	for(i=0;i<pic.height;i++)
		for(j=0;j<pic.width;j++)
			pic.rgb[i][j].red=pic.rgb[i][j].green=pic.rgb[i][j].blue=grayscale(pic.rgb[i][j]);
}
int createBWImage(	struct bmpheader header, struct infohead dibheader,struct Image pic){
	
	int i;
	FILE *fpw=fopen("BMgray.bmp","wb");
	if (fpw==NULL) return 1;	
	
	RGBImageToGrayscale(pic);
	
	fwrite(&header.name0,1,1,fpw);
	fwrite(&header.name1,1,1,fpw);
	fwrite(&header.size,3*sizeof(int),1,fpw);
	
	fwrite(&dibheader,sizeof(struct infohead),1,fpw);
	fseek(fpw,header.image_offset,SEEK_SET);
	
	for(i=pic.height-1;i>=0;i--){
		fwrite(pic.rgb[i],pic.width,sizeof(struct RGB),fpw);
	}
	
	fclose(fpw);
	return 0;
		
}
void RGBFlipImage(struct Image pic){
	int i,j;								
	unsigned char T;
	struct RGB PT;
	for(i=0;i<pic.height;i++)
		for(j=i+1;j<pic.width;j++)
		{
										
			PT=pic.rgb[i][j];
			pic.rgb[i][j]=pic.rgb[j][i];
			pic.rgb[j][i]=PT;
					
		}

	
}

int flipped(struct bmpheader header, struct infohead dibheader,struct Image pic){
	int i;
	FILE *fpw=fopen("Flipped.bmp","wb");
	if (fpw==NULL) return 1;
	RGBFlipImage(pic);
	fwrite(&header.name0,1,1,fpw);
	fwrite(&header.name1,1,1,fpw);
	fwrite(&header.size,3*sizeof(int),1,fpw);
	fwrite(&dibheader,sizeof(struct infohead),1,fpw);
	fseek(fpw,header.image_offset,SEEK_SET);
	for(i=pic.height-1;i>=0;i--){
		fwrite(pic.rgb[i],pic.width,sizeof(struct RGB),fpw);
	}
	
	fclose(fpw);
	return 0;
		
}

void rgbrotate90(struct Image pic){
	int i,j;
	unsigned char T;
	struct RGB PT;	
	RGBFlipImage(pic);
	for(i=0;i<pic.height;i++)
		for(j=0;j<pic.width/2;j++)
		{
			PT=pic.rgb[i][j];
			pic.rgb[i][j]=pic.rgb[i][pic.width-j];
			pic.rgb[i][pic.width-j]=PT;			
		}
}

int rotate90(struct bmpheader header, struct infohead dibheader,struct Image pic){
	
	int i;
	FILE *fpw=fopen("Rot90.bmp","wb");
	if (fpw==NULL) return 1;
	
	rgbrotate90(pic);
	
	fwrite(&header.name0,1,1,fpw);
	fwrite(&header.name1,1,1,fpw);
	fwrite(&header.size,3*sizeof(int),1,fpw);
	
	fwrite(&dibheader,sizeof(struct infohead),1,fpw);
	fseek(fpw,header.image_offset,SEEK_SET);
	for(i=pic.height-1;i>=0;i--){
		fwrite(pic.rgb[i],pic.width,sizeof(struct RGB),fpw);
	}
	fclose(fpw);
	return 0;
		
}

void openbmpfile(){
	struct bmpheader header;
	struct infohead dibheader;													
	FILE *fp=fopen("lena.bmp","rb");
	if(fp==NULL) return 1;																			
	
	fread(&header.name0,1,1,fp);
	fread(&header.name1,1,1,fp);
	fread(&header.size,3*sizeof(int),1,fp);
	printf("\n\nFor The Invoked Image:");
	printf("\nFirst two characters:%c%c\n",header.name0,header.name1);
	if((header.name0!='B')&&(header.name1!='M'))
	{
			printf("\nNot a Bitmap Image:");
			fclose(fp);
			return;
	}
	
	printf("Size:%d\n",header.size);
	printf("Offset:%d\n",header.image_offset);
	fread(&dibheader.header_size,sizeof(struct infohead),1,fp);
	printf("Header size:%d\nWidth:%d\nheight:%d\nColor planes:%d\nBits per pixel:%d\nCompression:%d\nImage Size:%d\n",dibheader.header_size,dibheader.width,dibheader.height,dibheader.colorplanes,dibheader.bitsperpixel,dibheader.compression,dibheader.image_size);
	if((dibheader.header_size!=40)||(dibheader.compression!=0)||(dibheader.bitsperpixel!=24))
	{
		fclose(fp);
		return;
	}
	
	fseek(fp,header.image_offset,SEEK_SET);
	struct Image image=newimage(fp,dibheader.height,dibheader.width);
	createBWImage(header,dibheader,image);
	
	fseek(fp,header.image_offset,SEEK_SET);															
	image=newimage(fp,dibheader.height,dibheader.width);
	flipped(header,dibheader,image);
	
	fseek(fp,header.image_offset,SEEK_SET);
	image=newimage(fp,dibheader.height,dibheader.width);
	rotate90(header,dibheader,image);
	
	int scale=2;
	struct infohead dibheader2=dibheader;										
	struct bmpheader header2=header;
	dibheader2.height=dibheader.height*scale;
	dibheader2.width=dibheader.width*scale;
	dibheader2.image_size=dibheader2.height*dibheader2.width*3;
	header2.size=dibheader2.image_size+header2.image_offset;
	
	printf("\n\nFor The Image to be Upscaled:");
	printf("\nFirst two characters:%c%c\n",header2.name0,header2.name1);
	printf("Size:%d\n",header2.size);
	printf("Offset:%d\n",header2.image_offset);
	printf("Header size:%d\nWidth:%d\nheight:%d\nColor planes:%d\nBits per pixel:%d\nCompression:%d\nImage Size:%d\n",dibheader2.header_size,dibheader2.width,dibheader2.height,dibheader2.colorplanes,dibheader2.bitsperpixel,dibheader2.compression,dibheader2.image_size);
	fseek(fp,header.image_offset,SEEK_SET);
	image=newimage(fp,dibheader.height,dibheader.width);
	struct Image image2;											
	image2=scaledimage(dibheader2.height,dibheader2.width,image,scale);
	scaled(header2,dibheader2,image2,scale);
	
	dibheader2.height=dibheader.height*2;
	dibheader2.width=dibheader.width*2;
	dibheader2.image_size=dibheader2.height*dibheader2.width*3;
	header2.size=dibheader2.image_size+header2.image_offset;
	
	fseek(fp,header.image_offset,SEEK_SET);
	image=newimage(fp,dibheader.height,dibheader.width);											
	image2=createimage(dibheader2.height,dibheader2.width);
	fseek(fp,header.image_offset,SEEK_SET);
	image=newimage(fp,dibheader.height,dibheader.width);
	rotate45(header2,dibheader2,image2,image);
	fclose(fp);
	freeImage(image);
	freeImage(image2);
	return;
}

int main(){
	openbmpfile();
	Mat img1 = imread("C:/cornmain.bmp", -1);
	for (cv::MatIterator_<cv::Vec3b> it = img1.begin<cv::Vec3b>(); it != img1.end<cv::Vec3b>(); ++it)
	{
		(*it)[0] = 0;
	}
	imwrite("C:/opencv/CornNotBlue.bmp", img1);
	Mat img1 = imread("C:/cornmain.bmp", -1);
	for (cv::MatIterator_<cv::Vec3b> it = img1.begin<cv::Vec3b>(); it != img1.end<cv::Vec3b>(); ++it)
	{
		(*it)[1] = 0;
	}
	imwrite("C:/opencv/CornNotGreen.bmp", img1);
	Mat img1 = imread("C:/cornmain.bmp", -1);
	for (cv::MatIterator_<cv::Vec3b> it = img1.begin<cv::Vec3b>(); it != img1.end<cv::Vec3b>(); ++it)
	{
		(*it)[2] = 0;
	}
	imwrite("C:/opencv/CornNotRed.bmp", img1);
	return 0;
}