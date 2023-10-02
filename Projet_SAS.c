#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int lesTachesARealiser = 0;
int lesTachesEnCours = 0;
int lesTachesFinalisee = 0;

struct Date {
    int jour;
    int mois;
    int annee;
};

struct Tache {
    char identi[50];
    char titre[50];
    char descr[200];
    int statut;
    struct Date deadline;
    time_t creation_date;   // Date de création de la tâche
};

struct Tache Taches[100]; // Ajoutez la taille selon vos besoins
int taskCount = 0;

const char *statutStrings[] = {
    "À réaliser",
    "En cours",
    "Finalisée"
};

// Fonction pour convertir la structure Date en structure tm
struct tm convertirLaDate(struct Date date) {
    struct tm dateConvertie;
    memset(&dateConvertie, 0, sizeof(struct tm)); // Initialisation avec des zéros
    dateConvertie.tm_year = date.annee - 1900;
    dateConvertie.tm_mon = date.mois - 1;
    dateConvertie.tm_mday = date.jour;
    return dateConvertie;
}

// Comparaison de tâches par titre (pour le tri)
int comparaisonParTitre(const void *a, const void *b) {
    return strcmp(((struct Tache *)a)->titre, ((struct Tache *)b)->titre);
}

// Comparaison de tâches par date limite (pour le tri)
int comparaisonParDeadline(const void *a, const void *b) {
    struct Tache *taskA = (struct Tache *)a;
    struct Tache *taskB = (struct Tache *)b;

    // Convertir les dates limites en time_t pour la comparaison
    struct tm tmA = convertirLaDate(taskA->deadline);
    struct tm tmB = convertirLaDate(taskB->deadline);

    time_t timeA = mktime(&tmA);
    time_t timeB = mktime(&tmB);

    if (timeA < timeB) return -1;
    else if (timeA > timeB) return 1;
    else return 0;
}

// Calcul de la différence en jours entre deux dates
int differenceDesDate(struct Date date1, struct Date date2) {
    struct tm tm1 = convertirLaDate(date1);
    struct tm tm2 = convertirLaDate(date2);

    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);

    return (int)difftime(time2, time1) / (60 * 60 * 24);
}

// Affichage des tâches dans une plage de dates limites donnée
void displayTachesWithDeadline(struct Date DateActuelle, int days) {
    if (taskCount == 0) {
        printf("Aucune tâche à afficher.\n");
        return;
    }
    printf("Liste des tâches avec une échéance de %d jours ou moins:\n", days);
    for (int i = 0; i < taskCount; i++) {
        int joursRestant = differenceDesDate(DateActuelle, Taches[i].deadline);
        if (joursRestant <= days) {
            printf("----------------------------\n");
            printf("ID: %d\n", i + 1);
            printf("Titre: %s\n", Taches[i].titre);
            printf("Description: %s\n", Taches[i].descr);
            printf("Statut: %s\n", statutStrings[Taches[i].statut]);

            // Conversion de la date limite en structure tm
            struct tm deadlineDate = convertirLaDate(Taches[i].deadline);
          
            // Utilisation de strftime pour afficher la date limite au format "jour/mois/année"
            char formattedDate[20];
            strftime(formattedDate, sizeof(formattedDate), "%d/%m/%Y", &deadlineDate);

            printf("Date limite: %s\n", formattedDate);

          // Afficher la date de création au format "jour/mois/année"
        struct tm creationDate = *localtime(&Taches[i].creation_date);
        strftime(formattedDate, sizeof(formattedDate), "%d/%m/%Y", &creationDate);
        printf("----------------------------\n");
        printf("Date de création: %s\n", formattedDate);
      
        printf("----------------------------\n");
          
            printf("Jours restants: %d\n", joursRestant);
            printf("----------------------------\n");
        }
    }
}

// Fonction pour modifier une tâche par son ID

void modifyTache(int id) {
    if (id >= 1 && id <= taskCount) {
        struct Tache *task = &Taches[id - 1]; // Ajuster pour l'indexation à partir de 0

        int choice;
        do {
            printf("Modification de la tâche ID %d:\n", id);
            printf("1. Modifier le titre\n");
            printf("2. Modifier la description\n");
            printf("3. Modifier le statut (0: à réaliser, 1: en cours, 2: finalisée)\n");
            printf("4. Modifier la date limite (jour mois année)\n");
            printf("5. Quitter la modification\n");
            printf("Choix : ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Entrer le nouveau titre : ");
                    scanf("%s", task->titre);
                    break;
                case 2:
                    printf("Entrer la nouvelle description : ");
                    scanf("%s", task->descr);
                    break;
                case 3:
                    printf("Entrer le nouveau statut (0: à réaliser, 1: en cours, 2: finalisée) : ");
                    scanf("%d", &task->statut);
                    break;
                case 4:
                    printf("Entrer la nouvelle date limite (jour mois année) : ");
                    scanf("%d %d %d", &task->deadline.jour, &task->deadline.mois, &task->deadline.annee);
                    break;
                case 5:
                    printf("Modification terminée.\n");
                    break;
                default:
                    printf("Choix invalide. Veuillez réesayer.\n");
            }
        } while (choice != 5);
    }
    else {
        printf("ID de tâche invalide.\n");
    }
}

// Fonction pour supprimer une tâche par son ID
void deleteTache(int id) {
    if (id >= 1 && id <= taskCount) {
        for (int i = id - 1; i < taskCount - 1; i++) {
            Taches[i] = Taches[i + 1];
        }
        taskCount--;
        printf("Tâche ID %d supprimée avec succès.\n", id);
    } else {
        printf("ID de tâche invalide.\n");
    }
}

// Fonction pour rechercher une tâche par son ID
void searchTacheById(int id) {
    if (id >= 1 && id <= taskCount) {
        printf("----------------------------\n");
        printf("Tâche ID %d:\n", id);
        printf("Titre: %s\n", Taches[id - 1].titre);
        printf("Description: %s\n", Taches[id - 1].descr);
        printf("Statut: %s\n", statutStrings[Taches[id - 1].statut]);
        

        // Conversion de la date limite en structure tm
        struct tm deadlineDate = convertirLaDate(Taches[id - 1].deadline);

        // Utilisation de strftime pour afficher la date limite au format "jour/mois/année"
        char formattedDate[20];
        strftime(formattedDate, sizeof(formattedDate), "%d/%m/%Y", &deadlineDate);

        printf("Date limite: %s\n", formattedDate);
        int i;
        // Afficher la date de création au format "jour/mois/année"
        struct tm creationDate = *localtime(&Taches[i].creation_date);
        strftime(formattedDate, sizeof(formattedDate), "%d/%m/%Y", &creationDate);
        printf("----------------------------\n");
        printf("Date de création: %s\n", formattedDate);
      
        printf("----------------------------\n");
    } else {
        printf("ID de tâche invalide.\n");
    }
}

// Fonction pour rechercher une tâche par titre
void searchTacheByTitle(const char *title) {
    int found = 0;
    for (int i = 0; i < taskCount; i++) {
        if (strcmp(title, Taches[i].titre) == 0) {
            found = 1;
            printf("----------------------------\n");
            printf("Tâche avec le titre '%s' (ID %d):\n", title, i + 1);
            printf("Titre: %s\n", Taches[i].titre);
            printf("Description: %s\n", Taches[i].descr);
            printf("Statut: %s\n", statutStrings[Taches[i].statut]);
            printf("----------------------------\n");

            // Conversion de la date limite en structure tm
            struct tm deadlineDate = convertirLaDate(Taches[i].deadline);

            // Utilisation de strftime pour afficher la date limite au format "jour/mois/année"
            char formattedDate[20];
            strftime(formattedDate, sizeof(formattedDate), "%d/%m/%Y", &deadlineDate);

            printf("Date limite: %s\n", formattedDate);

            // Afficher la date de création au format "jour/mois/année"
        struct tm creationDate = *localtime(&Taches[i].creation_date);
        strftime(formattedDate, sizeof(formattedDate), "%d/%m/%Y", &creationDate);

        printf("Date de création: %s\n", formattedDate);
          
            printf("----------------------------\n");
        }
    }
    if (!found) {
        printf("Aucune tâche avec le titre '%s' n'a été trouvée.\n", title);
    }
}

// Fonction pour rechercher une tâche par deadline
void searchTacheByDeadline(struct Date deadlineDate) {
    int found = 0;
    printf("Tâches avec la date limite (jour mois année) avant ou le jour même : %d/%d/%d\n", deadlineDate.jour, deadlineDate.mois, deadlineDate.annee);
    for (int i = 0; i < taskCount; i++) {
        struct Date taskDeadline = Taches[i].deadline;
        if (taskDeadline.annee < deadlineDate.annee ||
            (taskDeadline.annee == deadlineDate.annee && taskDeadline.mois < deadlineDate.mois) ||
            (taskDeadline.annee == deadlineDate.annee && taskDeadline.mois == deadlineDate.mois && taskDeadline.jour <= deadlineDate.jour)) {
            found = 1;
            printf("----------------------------\n");
            printf("Tâche ID %d:\n", i + 1);
            printf("Titre: %s\n", Taches[i].titre);
            printf("Description: %s\n", Taches[i].descr);
            printf("Statut: %s\n", statutStrings[Taches[i].statut]);
            printf("Date limite: %d/%d/%d\n", taskDeadline.jour, taskDeadline.mois, taskDeadline.annee);
            // Afficher la date de création au format "jour/mois/année"
            struct tm creationDate = *localtime(&Taches[i].creation_date);
            char formattedDate[20];
            strftime(formattedDate, sizeof(formattedDate), "%d/%m/%Y", &creationDate);
            printf("Date de création: %s\n", formattedDate);
        }
    }
    if (!found) {
        printf("Aucune tâche avec une date limite avant ou le jour même n'a été trouvée.\n");
    }
}


// Fonction pour ajouter une nouvelle tâche
void addTache() {
    if (taskCount < 100) {
        printf("Ajouter une nouvelle tâche:\n");
        
        printf("Titre: ");
       getchar();
        scanf("%[^\n]", Taches[taskCount].titre);
        printf("Description: ");
      getchar();
        scanf("%[^\n]", Taches[taskCount].descr);
        printf("Statut (0: à réaliser, 1: en cours, 2: finalisée): ");
        scanf("%d", &Taches[taskCount].statut);
        printf("Deadline (jour, mois, année): ");
        scanf("%d %d %d", &Taches[taskCount].deadline.jour, &Taches[taskCount].deadline.mois, &Taches[taskCount].deadline.annee);
      
        Taches[taskCount].creation_date = time(NULL);


    }
    else {
        printf("La liste de tâches est pleine, vous ne pouvez pas ajouter plus de tâches.\n");
    }
}

// Fonction par afficher le nomber de jours restants jusqu'au delai de chaque tache

void joursRestants(struct Date DateActuelle) {
    if (taskCount == 0) {
        printf("Aucune tâche à afficher.\n");
        return;
    }

    printf("Nombre de jours restants jusqu'au délai de chaque tâche:\n");
    for (int i = 0; i < taskCount; i++) {
        int joursRestant = differenceDesDate(DateActuelle, Taches[i].deadline);
        printf("----------------------------\n");
        printf("Tâche ID %d\n", i + 1);
        printf("Titre: %s\n", Taches[i].titre);
        printf("Jours restants: %d\n", joursRestant);
        printf("----------------------------\n");
    }
}



// Fonction pour afficher toutes les tâches
void displayTaches() {
    if (taskCount == 0) {
        printf("Aucune tâche à afficher.\n");
        return;
    }

    printf("Liste de toutes les tâches:\n");
    for (int i = 0; i < taskCount; i++) {
        printf("----------------------------\n");
        printf("ID: %d\n", i + 1);
        printf("Titre: %s\n", Taches[i].titre);
        printf("Description: %s\n", Taches[i].descr);
        printf("Statut: %s\n", statutStrings[Taches[i].statut]);

        // Conversion de la date limite en structure tm
        struct tm deadlineDate = convertirLaDate(Taches[i].deadline);

        // Utilisation de strftime pour afficher la date limite au format "jour/mois/année"
        char formattedDate[20];
        strftime(formattedDate, sizeof(formattedDate), "%d/%m/%Y", &deadlineDate);

        printf("Date limite: %s\n", formattedDate);

        // Afficher la date de création au format "jour/mois/année"
        struct tm creationDate = *localtime(&Taches[i].creation_date);
        strftime(formattedDate, sizeof(formattedDate), "%d/%m/%Y", &creationDate);
        printf("----------------------------\n");
        printf("Date de création: %s\n", formattedDate);
        printf("----------------------------\n");
    }
}

int main() {
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Ajouter une nouvelle tâche\n");
        printf("2. Ajouter plusieur nouvelle tâches \n");
        printf("3. Afficher la liste de toutes les tâches\n");
        printf("4. Modifier une tâche\n");
        printf("5. Supprimer une tâche\n");
        printf("6. Rechercher une tâche\n");
        printf("7. Afficher les statistiques\n");
        printf("8. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (taskCount < 100) {
                    addTache(&Taches[taskCount]);
                    taskCount++;
                    
                } else {
                    printf("La liste de tâches est pleine, vous ne pouvez pas ajouter plus de tâches.\n");
                }
                break;
            case 2: 
              printf("choiser le nomber des taches ajouter: \n");
                int i;
                int nbr;

                scanf("%d",&nbr );
              if(nbr<20){
                for(i=0; i<nbr; i++ ){
                 
                  addTache(&Taches[taskCount]);
                  taskCount++;
                }
                }
              else
                printf("Choix invalide. Veuillez réesayer.\n");
          break;
            case 3:
                printf("1. Afficher la liste de toutes les taches aliatoirement \n");
               printf("2. Afficher la liste de toutes les taches par ordre alphabitique.\n");
                printf("3. Afficher la liste de toutes les tâches par ordre deadline.\n");
                printf("4. Afficher les tâches dont le deadline est dans 3 jours ou moins.");
                printf("Choix : ");
                scanf("%d", &choice);
                switch (choice) {
                    case 1:
                        printf("Afficher la liste de toutes les taches aléatoirement \n");
                        displayTaches();
                        break;
                    case 2:
                        printf("Trier les tâches par ordre alphabétique:\n");
                        qsort(Taches, taskCount, sizeof(struct Tache), comparaisonParTitre);
                        displayTaches();
                        break;
                    case 3:
                        printf("Trier les tâches par deadline:\n");
                        qsort(Taches, taskCount, sizeof(struct Tache), comparaisonParDeadline);
                        displayTaches();
                        break;
                    case 4:
                         printf("Afficher les tâches avec une date limite de 3 jours ou moins:\n");
                         struct Date DateActuelle;
                         printf("Entrer la date actuelle (jour mois année): ");
                        scanf("%d %d %d", &DateActuelle.jour, &DateActuelle.mois, &DateActuelle.annee);
                        displayTachesWithDeadline(DateActuelle, 3);
    break;
                    default:
                        printf("Choix invalide.\n");
                }
                break;
      
            case 4:
                printf("Modifier une tâche (Entrer l'ID de la tâche) : ");
                int idToModify;
                scanf("%d", &idToModify);
                searchTacheById(idToModify);
                modifyTache(idToModify);
                break;
            case 5:
                printf("Supprimer une tâche (Entrer l'ID de la tâche) : ");
                int idToDelete;
                scanf("%d", &idToDelete);
                deleteTache(idToDelete);
                break;
            case 6:
                printf("1. Rechercher une tâche par son ID (Entrer l'ID de la tâche) : \n");
                printf("2. Rechercher une tâche par son titre (Entrer le titre) :\n ");
                printf("3. Rechercher des tâches par date limite (Entrer la date limite) :\n ");
                printf("Choix : ");
                scanf("%d", &choice);
                switch (choice) {
                    case 1:
                        printf("Rechercher une tâche par son ID (Entrer l'ID de la tâche) : ");
                        int idToSearch;
                        scanf("%d", &idToSearch);
                        searchTacheById(idToSearch);
                        break;
                    case 2:
                        printf("Rechercher une tâche par son titre (Entrer le titre) : ");
                        char titleToSearch[50];
                        scanf("%s", titleToSearch);
                        searchTacheByTitle(titleToSearch);
                        break;
                    case 3:
            printf("Rechercher des tâches par date limite (Entrer la date limite sous la forme jour mois année) : ");
            struct Date deadlineDate;
            scanf("%d %d %d", &deadlineDate.jour, &deadlineDate.mois, &deadlineDate.annee);
            searchTacheByDeadline(deadlineDate);
            break;
                    default:
                        printf("Choix invalide.\n");
                }
                break;
            case 7:

              printf("Choix \n");
              printf("1. Afficher les statistique generale \n");
              printf("2. Afficher le nombre de de jours restants jusqu'au delai chaque tache \n");
              printf("Choix : ");
                scanf("%d", &choice);
              
              switch(choice){
                case 1:
             
                  // Calculer les statistiques
                  lesTachesARealiser = 0;
                  lesTachesEnCours = 0;
                  lesTachesFinalisee = 0;
  
                  for (int i = 0; i < taskCount; i++) {
                      switch (Taches[i].statut) {
                          case 0:
                              lesTachesARealiser++;
                              break;
                          case 1:
                              lesTachesEnCours++;
                              break;
                          case 2:
                              lesTachesFinalisee++;
                              break;
                      }
                  
                  // Afficher les statistiques
                  printf("\n -----------------------------\n");
                  printf("|| Statistiques des tâches : ||\n");
                  printf(" -----------------------------\n");
                  printf(" Nombre total de tâches : %d\n", taskCount);
                  printf(" Tâches à réaliser : %d\n", lesTachesARealiser);
                  printf(" Tâches en cours : %d\n", lesTachesEnCours);
                  printf(" Tâches finalisées : %d\n", lesTachesFinalisee);
                  printf("----------------------------\n");
                    
              } 
                  break;
                case 2:
                
                   printf("Afficher le nombre de jours restants jusqu'au délai de chaque tâche:\n");
                   struct Date DateActuelle;
                   printf("Entrer la date actuelle (jour mois année): ");
                  scanf("%d %d %d", &DateActuelle.jour, &DateActuelle.mois, &DateActuelle.annee);
                  printf("\n -----------------------------\n");
                  joursRestants(DateActuelle);
                  printf("\n -----------------------------\n");
    break;
                default:
                        printf("Choix invalide.\n");
              }
      break;
          
            case 8:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide. Veuillez réesayer.\n");
        }
    } while (choice != 8);

    return 0;
}
