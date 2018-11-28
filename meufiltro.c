#include "meufiltro.h"

void inicializarWidgetsMeuFiltro() {
}

void adicionarWidgetsMeuFiltro(GtkWidget *container) {


}


struct RGB
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

struct HSV
{
    double H;
    double S;
    double V;
};

static double Min(double a, double b) {
    return a <= b ? a : b;
}

static double Max(double a, double b) {
    return a >= b ? a : b;
}

struct HSV RGBToHSV(struct RGB rgb) {
    double delta, min;
    double h = 0, s, v;

    min = Min(Min(rgb.R, rgb.G), rgb.B);
    v = Max(Max(rgb.R, rgb.G), rgb.B);
    delta = v - min;

    if (v == 0.0)
        s = 0;
    else
        s = delta / v;

    if (s == 0)
        h = 0.0;

    else
  
    {
        if (rgb.R == v)
            h = (rgb.G - rgb.B) / delta;
        else if (rgb.G == v)
            h = 2 + (rgb.B - rgb.R) / delta;
        else if (rgb.B == v)
            h = 4 + (rgb.R - rgb.G) / delta;

        h *= 60;

        if (h < 0.0)
            h = h + 360;
    }

    struct HSV hsv;
    hsv.H = h;
    hsv.S = s;
    hsv.V = v / 255;

    return hsv;
}

Imagem meuFiltro(Imagem origem,Imagem fundo, GdkRGBA cor) {
    struct RGB corFundoRGB ={(int) cor.red,(int) cor.green,(int) cor.blue};
    struct HSV corFundo = RGBToHSV(corFundoRGB);
    Imagem destino = alocarImagem(origem);
    for(int a = 0;a<origem.h;a++){
        for(int b = 0;b<origem.w;b++){
            struct RGB rgb ={origem.m[a][b][0],origem.m[a][b][1],origem.m[a][b][0]};
            struct HSV hsv = RGBToHSV(rgb);
            //if(origem.m[a][b][0] >= 0 && origem.m[a][b][0] <= 80  && origem.m[a][b][1] >= 100 && origem.m[a][b][1] <= 255  && origem.m[a][b][3] >= 0 && origem.m[a][b][3] <= 80){
            if(hsv.H >= corFundo.H-30 && hsv.H <= corFundo.H+30 && hsv.S >= 0.15 && hsv.V > 0.15){
                //if((origem.m[a][b][0]*origem.m[a][b][2]) !=0 && (origem.m[a][b][1]*origem.m[a][b][1]) / (origem.m[a][b][0]*origem.m[a][b][2]) >= 1.5){
                    destino.m[a][b][0] = fundo.m[a][b][0];
                    destino.m[a][b][1] = fundo.m[a][b][1];
                    destino.m[a][b][2] = fundo.m[a][b][2];
                /*}else{
                    destino.m[a][b][0] = (int)(fundo.m[a][b][0]*1.2);
                    destino.m[a][b][1] = (int)fundo.m[a][b][1];
                    destino.m[a][b][2] = (int)(fundo.m[a][b][2]*1.2);
                }*/
            }else{
                destino.m[a][b][0] = origem.m[a][b][0];
                destino.m[a][b][1] = origem.m[a][b][1];
                destino.m[a][b][2] = origem.m[a][b][2];
            }
        }
    }
    return destino;
}






