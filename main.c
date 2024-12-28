#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_CAPACITY 50
int current_booked_seats = 0;


typedef struct {
    char *name;
    char *phone;
    char *date;
    char *time;
    int guests;
} Reservation;


void addReservation(Reservation **reservations, int *count);
void viewReservations(Reservation *reservations, int count);
void cancelReservation(Reservation **reservations, int *count, int index);
void saveToFile(Reservation *reservations, int count);
void loadFromFile(Reservation **reservations, int *count);
int validateDate(const char *date);
int validateTime(const char *time);

int main() {
    Reservation *reservations = NULL;
    int count = 0, choice;


    loadFromFile(&reservations, &count);


    for (int i = 0; i < count; i++) {
        current_booked_seats += reservations[i].guests;
    }

    while (1) {
        printf("\n=== Systeme de Gestion des reservations ===\n");
        printf("Places reservees : %d/%d\n", current_booked_seats, MAX_CAPACITY);
        printf("1. Ajouter une reservation\n");
        printf("2. Voir toutes les reservations\n");
        printf("3. Annuler une reservation\n");
        printf("4. Sauvegarder et quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addReservation(&reservations, &count);
                break;
            case 2:
                viewReservations(reservations, count);
                break;
            case 3: {
                int index;
                printf("Entrez le numero de la reservation a annuler : ");
                scanf("%d", &index);
                cancelReservation(&reservations, &count, index - 1);
                break;
            }
            case 4:
                saveToFile(reservations, count);
                printf("Sortie du programme...\n");
                for (int i = 0; i < count; i++) {
                    free(reservations[i].name);
                    free(reservations[i].phone);
                    free(reservations[i].date);
                    free(reservations[i].time);
                }
                free(reservations);
                return 0;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    }
}


void addReservation(Reservation **reservations, int *count) {
    if (current_booked_seats >= MAX_CAPACITY) {
        printf("D�sol�, le restaurant est complet. Impossible d'ajouter une reservation.\n");
        return;
    }

    *reservations = realloc(*reservations, (*count + 1) * sizeof(Reservation));
    if (!*reservations) {
        printf("Erreur : echec de l'allocation memoire.\n");
        return;
    }

    Reservation *new_reservation = &(*reservations)[*count];
    new_reservation->name = malloc(100);
    new_reservation->phone = malloc(15);
    new_reservation->date = malloc(11);
    new_reservation->time = malloc(6);

    printf("Entrez le nom : ");
    scanf(" %[^\n]", new_reservation->name);
    printf("Entrez le numero de telephone : ");
    scanf("%s", new_reservation->phone);

    do {
        printf("Entrez la date (YYYY-MM-DD) : ");
        scanf("%s", new_reservation->date);
        if (!validateDate(new_reservation->date)) {
            printf("Format de date invalide. Reessayez.\n");
        }
    } while (!validateDate(new_reservation->date));

    do {
        printf("Entrez l'heure (HH:MM) : ");
        scanf("%s", new_reservation->time);
        if (!validateTime(new_reservation->time)) {
            printf("Format de l'heure invalide. Reessayez.\n");
        }
    } while (!validateTime(new_reservation->time));

    int requested_guests;
    printf("Entrez le nombre de personnes : ");
    while (scanf("%d", &requested_guests) != 1 || requested_guests <= 0) {
        printf("Entree invalide. Entrez un nombre positif : ");
        while (getchar() != '\n');
    }

    if (current_booked_seats + requested_guests > MAX_CAPACITY) {
        printf("Pas assez de places disponibles. Il reste %d places.\n",
               MAX_CAPACITY - current_booked_seats);
        return;
    }

    new_reservation->guests = requested_guests;
    current_booked_seats += requested_guests;

    (*count)++;
    printf("reservation ajoutee avec succes. Places restantes : %d.\n",
           MAX_CAPACITY - current_booked_seats);
}


void viewReservations(Reservation *reservations, int count) {
    if (count == 0) {
        printf("Aucune reservation trouvee.\n");
        return;
    }

    printf("\n=== Liste des reservations ===\n");
    for (int i = 0; i < count; i++) {
        printf("reservation #%d\n", i + 1);
        printf("Nom : %s\n", reservations[i].name);
        printf("Telephone : %s\n", reservations[i].phone);
        printf("Date : %s\n", reservations[i].date);
        printf("Heure : %s\n", reservations[i].time);
        printf("Personnes : %d\n", reservations[i].guests);
        printf("-------------------------\n");
    }
}


void cancelReservation(Reservation **reservations, int *count, int index) {
    if (index < 0 || index >= *count) {
        printf("Index de reservation invalide.\n");
        return;
    }

    current_booked_seats -= (*reservations)[index].guests;

    free((*reservations)[index].name);
    free((*reservations)[index].phone);
    free((*reservations)[index].date);
    free((*reservations)[index].time);

    for (int i = index; i < *count - 1; i++) {
        (*reservations)[i] = (*reservations)[i + 1];
    }

    *reservations = realloc(*reservations, (*count - 1) * sizeof(Reservation));
    (*count)--;

    printf("R�servation annulee avec succes. Places restantes : %d.\n",
           MAX_CAPACITY - current_booked_seats);
}


void saveToFile(Reservation *reservations, int count) {
    FILE *file = fopen("reservations.txt", "w");
    if (!file) {
        printf("Erreur : impossible d'ouvrir le fichier pour la sauvegarde.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s|%s|%s|%s|%d\n",
                reservations[i].name, reservations[i].phone, reservations[i].date,
                reservations[i].time, reservations[i].guests);
    }

    fclose(file);
    printf("reservations sauvegardees avec succes.\n");
}


void loadFromFile(Reservation **reservations, int *count) {
    FILE *file = fopen("reservations.txt", "r");
    if (!file) {
        printf("Aucune reservation enregistree. Nouveau depart.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        *reservations = realloc(*reservations, (*count + 1) * sizeof(Reservation));
        if (!*reservations) {
            printf("Erreur : echec de l'allocation memoire.\n");
            fclose(file);
            return;
        }

        Reservation *new_reservation = &(*reservations)[*count];
        new_reservation->name = malloc(100);
        new_reservation->phone = malloc(15);
        new_reservation->date = malloc(11);
        new_reservation->time = malloc(6);

        sscanf(line, "%99[^|]|%14[^|]|%10[^|]|%5[^|]|%d",
               new_reservation->name, new_reservation->phone,
               new_reservation->date, new_reservation->time, &new_reservation->guests);

        current_booked_seats += new_reservation->guests;
        (*count)++;
    }

    fclose(file);
    printf("reservations chargees avec succes.\n");
}


int validateDate(const char *date) {
    int year, month, day;
    return sscanf(date, "%4d-%2d-%2d", &year, &month, &day) == 3;
}


int validateTime(const char *time) {
    int hour, minute;
    return sscanf(time, "%2d:%2d", &hour, &minute) == 2;
}
