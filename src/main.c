#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include "search.h"
#include "sort.h"
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

GtkWidget *see_credits;
GtkWidget *window_game;
GtkWidget *window;
GtkWidget *window_n_par;
GtkWidget *window_par;
GtkWidget *window_nickname;
GtkWidget *score;
GtkWidget *player;
GtkEntry *nick_entry;
GtkEntryBuffer *entry_buffer;
GtkImage *images[30];
GtkBuilder *builder;
FILE *file_highscores;
int scores[5];
int card_temp = 0;
int points = 0;
int imageIndex;
int matrix[6][5][2];
char nickname[30];
char nicks[5];

void link_images();
void load_images();
void load_image_back();
void fill_matrix ();
void on_btn_ok_n_par_clicked ();
void on_btn_ok_par_clicked ();
void on_btn_nickname_ok_clicked ();
void read_highscores ();

int main(int argc, char *argv[]) {

    srand(time(NULL));

    file_highscores = fopen("highscores.txt", "r+");

    read_highscores ();

    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade.xml", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
 
    //Linkando os widgets criados
    see_credits = GTK_WIDGET(gtk_builder_get_object(builder, "window_credits"));
    window_game = GTK_WIDGET(gtk_builder_get_object(builder, "window_playgame"));
    window_par = GTK_WIDGET(gtk_builder_get_object(builder, "window_confirm_par"));
    window_n_par = GTK_WIDGET(gtk_builder_get_object(builder, "window_confirm_n_par"));
    window_nickname = GTK_WIDGET(gtk_builder_get_object(builder, "window_nickname"));
    nick_entry = GTK_WIDGET(gtk_builder_get_object(builder, "txt_nick_entry"));
    score = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_score"));
    player = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_player"));

    fill_matrix(matrix);
    link_images();
    load_images(matrix);

    g_object_unref(builder);
    gtk_widget_show(window);                
    gtk_main();
 
    fclose(file_highscores);

    return 0;
}

void read_highscores () {
		
	//int i = 0;
	int temp1 = 0;
	int temp2 = 0;
	char temp[50];

	for(int i = 0; i < 10; i++){

        //temp[i] = (char*)malloc(50 * sizeof(char));

        //break;

        fscanf(file_highscores, "%s", temp);

        if (i % 2 == 0){
        	scores[temp1] = atoi(temp);
        	printf("%d\t", scores[temp1]);
        	temp1++;
        } else {
        	nicks[temp2] = (char*)malloc(30 * sizeof(char));
        	nicks[temp2] = temp;
        	printf("%s\n", temp);
        	temp2++;
        }



        //fgets(temp, 10, (FILE*)file_highscores);

        //printf("%s\n", temp);
    }

	// while(1){
		
	// 	fscanf(file_highscores, "%s", temp);

	// 	if(i % 2 == 0){
	// 		scores[temp1] = atoi(temp);
	// 		printf("%d\n", scores[temp1]);
	// 		temp1++;
	// 	} else {
	// 		nicks[temp2] = (char*)malloc(sizeof(char));
	// 		sprintf(nicks[temp2], "%s", temp);
	// 		// fscanf(temp, "%s", nicks[temp2]);
	// 		printf("%s\n", nicks[temp2]);
	// 		temp2++;
	// 	}
	// 	i++;
	// }
}

//Fechar janela no X
void on_window_main_destroy() {

    gtk_main_quit();  

}

void on_window_playgame_destroy () {

	gtk_main_quit();

}

void on_btn_playgame_clicked () {

    gtk_widget_show(GTK_WIDGET(window_nickname));
 	gtk_widget_hide(window);

}

void on_btn_creditos_clicked () {

    gtk_dialog_run(GTK_DIALOG(see_credits));
    gtk_widget_hide(see_credits);

}

void on_btn_nickname_ok_clicked () {

	char temp[50];

	entry_buffer = gtk_entry_get_buffer (nick_entry);
	strcpy(nickname, gtk_entry_buffer_get_text (entry_buffer));

	strcpy(temp, "Jogador: ");
	strcat(temp, nickname);
	gtk_label_set_text(GTK_LABEL(player), temp);

	printf("%s\n", nickname);

	gtk_widget_show(GTK_WIDGET(window_game));
	gtk_widget_hide(window_nickname);
}

void link_images () {

    for (int i = 0; i < 30; i++) {

        char imageIndex[30];
        char buffer[3];

        strcpy(imageIndex, "image");
        sprintf(buffer, "%d", i+1);
        strcat(imageIndex, buffer);

        images[i] = GTK_IMAGE(gtk_builder_get_object(builder, imageIndex));

    }

}

void load_images () {

    int k = 0;

    for(int i = 0; i < 6; i++){

        for(int q = 0; q < 5; q++){

            if(matrix[i][q][1] == 0){
                
             char imageName[30];
             char buffer[3];

             strcpy(imageName, "images/card_");
             sprintf(buffer, "%d", matrix[i][q][0]);
             strcat(imageName, buffer);
             strcat(imageName, ".png");

             gtk_image_set_from_file(images[k], imageName);

            } else {
                
                gtk_image_set_from_file(images[k], "images/card_back.png");

            }
         
            k++;

        }

    }

}

void fill_matrix () {

    int temp; 
    int numbers[15];
    bool exit = false;
    int i = 0;

    while(1){


        if(i == 15)
            break;

        temp = rand() % 52 + 1;

        if(!sequentialsearch(numbers, 15, temp)){
            numbers[i] = temp;
            i++;
        }

    }

    for(int i = 0; i < 6; i++){

        for(int q = 0; q < 5; q++){
            matrix[i][q][0] = NULL;
            matrix[i][q][1] = 1;
        }

    }

    for(int i = 0; i < 15; i++){

        while(1){

            int position = rand() % 30; 

            if(matrix[position / 5][position % 5][0] == NULL){
                matrix[position / 5][position % 5][0] = numbers[i];
                break;
            }

        }
        exit = false;

        while(1){

            int position = rand() % 30; 

            if(matrix[position / 5][position % 5][0] == NULL){
                matrix[position / 5][position % 5][0] = numbers[i];
                break;
            }

        }

        exit = false;
    }


}

void on_window_confirm_n_par_destroy () {

    on_btn_ok_n_par_clicked();

}

void on_window_confirm_par_destroy () {

    on_btn_ok_par_clicked();

}

void on_btn_ok_n_par_clicked () {

    points--;
    char points_c[30];
    char buffer_lbl[30];
    strcpy(points_c, "Pontos: ");
    sprintf(buffer_lbl, "%d", points);
    strcat(points_c, buffer_lbl);
    gtk_label_set_text(GTK_LABEL(score), points_c);
    gtk_image_set_from_file(images[imageIndex], "images/card_back.png");
    gtk_image_set_from_file(images[card_temp-1], "images/card_back.png");
    card_temp = 0;
    gtk_widget_hide(window_n_par);

}

void on_btn_ok_par_clicked () {

    points++;
    char points_c[30];
    char buffer_lbl[30];
    strcpy(points_c, "Pontos: ");
    sprintf(buffer_lbl, "%d", points);
    strcat(points_c, buffer_lbl);
    gtk_label_set_text(GTK_LABEL(score), points_c);
    gtk_widget_hide(window_par);

}

void on_btn_1_clicked () {

    imageIndex = 0;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_2_clicked () {

    imageIndex = 1;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_3_clicked () {

    imageIndex = 2;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_4_clicked () {

    imageIndex = 3;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }

    }
}

void on_btn_5_clicked () {

    imageIndex = 4;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_6_clicked () {

    imageIndex = 5;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_7_clicked () {

    imageIndex = 6;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_8_clicked () {

    imageIndex = 7;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_9_clicked () {

    imageIndex = 8;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_10_clicked () {

    imageIndex = 9;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_11_clicked () {

    imageIndex = 10;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_12_clicked () {

    imageIndex = 11;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_13_clicked () {

    imageIndex = 12;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_14_clicked () {

    imageIndex = 13;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_15_clicked () {

    imageIndex = 14;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_16_clicked () {

    imageIndex = 15;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_17_clicked () {

    imageIndex = 16;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_18_clicked () {

    imageIndex = 17;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_19_clicked () {

    imageIndex = 18;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_20_clicked () {

    imageIndex = 19;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_21_clicked () {

    imageIndex = 20;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_22_clicked () {

    imageIndex = 21;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_23_clicked () {

    imageIndex = 22;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_24_clicked () {

    imageIndex = 23;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_25_clicked () {

    imageIndex = 24;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_26_clicked () {

    imageIndex = 25;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_27_clicked () {

    imageIndex = 26;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_28_clicked () {

    imageIndex = 27;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_29_clicked () {

    imageIndex = 28;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}

void on_btn_30_clicked () {

    imageIndex = 29;

    if (matrix[imageIndex/5][imageIndex%5][1] == 0) {
        return;
    }

    if (card_temp == imageIndex+1) {
        return;
    }

    matrix[imageIndex/5][imageIndex%5][1] = 0;

    if (card_temp == 0) {

        char imageName[30];
        char buffer[3];

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);
        card_temp = imageIndex+1;

    } else {

        char imageName[30];
        char buffer[3];

        matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 0;

        strcpy(imageName, "images/card_");
        sprintf(buffer, "%d", matrix[imageIndex/5][imageIndex%5][0]);
        strcat(imageName, buffer);
        strcat(imageName, ".png");

        gtk_image_set_from_file(images[imageIndex], imageName);

        if (matrix[imageIndex/5][imageIndex%5][0] == matrix[(card_temp-1)/5][(card_temp-1)%5][0]) {

            gtk_widget_show(GTK_WIDGET(window_par));
            card_temp = 0;

        } else {

            gtk_widget_show(GTK_WIDGET(window_n_par));
            matrix[imageIndex/5][imageIndex%5][1] = 1;
            matrix[(card_temp-1)/5][(card_temp-1)%5][1] = 1;

        }
    }
}