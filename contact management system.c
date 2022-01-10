#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<stdlib.h>
#include<dos.h>
  
struct contact

{
    long long ph;
    char name[20];
} ct;

char query[20],name[20];

FILE *fp, *ft;

int i,n,ch,l,found;

int main()

{

main:

    system("cls");    /* ************Main menu ***********************  */
    printf("\n\t **** Welcome to Contact Management System ****");
    printf("\n\n\n\t\t\tMAIN MENU\n\t\t=====================\n\t\t[1] Add a New Contact\n\t\t[2] List all Contacts\n\t\t[3] Search for Contact\n\t\t[4] Edit a Contact\n\t\t[5] Delete a Contact\n\t\t[0] Exit\n\t\t=================\n\t\t");

    printf("Enter Your Choice: ");

    scanf("%d",&ch);

    switch(ch)

    {
	//This case is used for Exit//
    case 0:

        printf("\n\n\t\tAre You Sure To Exit?");

        break;

        /* *********************Add new contacts************  */
    case 1:

        system("cls");

        fp=fopen("contact.dll","a");

        for (;;)

        {
            fflush(stdin);

            printf("To Exit Enter Blank Space in the Name Input\nName (Use identical): ");

            scanf("%[^\n]",&ct.name);

            if(stricmp(ct.name,"")==0 || stricmp(ct.name," ")==0)

                break;

            fflush(stdin);

            printf("Phone: ");

            scanf("%lld",&ct.ph);

            fflush(stdin);

            printf("\n");

            fwrite(&ct,sizeof(ct),1,fp);

        }

        fclose(fp);

        break;

        /* *********************List of contacts*************************  */

    case 2:

        system("cls");

        printf("\n\t\t================================\n\t\t\tList OF CONTACTS\n\t\t================================\n\nName\t\tPhone No\t=================================================================\n\n");

        for(i=97; i<=122; i=i+1)

        {
            fp=fopen("contact.dll","r");

            fflush(stdin);

            found=0;

            while(fread(&ct,sizeof(ct),1,fp)==1)

            {

                if(ct.name[0]==i || ct.name[0]==i-32)

                {

                    printf("\nName\t: %s\nPhone\t: %lld\n",ct.name,ct.ph);

                    found++;

                }

            }

            if(found!=0)

            {
                printf("===========================================================");

                getch();
            }

            fclose(fp);

        }

        break;

        /* *******************search contacts**********************  */
	//This case is used search for Contact //
    case 3:

        system("cls");

        do

        {

            found=0;

            printf("\n\n\t..::CONTACT SEARCH\n\t===========================\n\t..::Name of contact to search: ");

            fflush(stdin);

            scanf("%[^\n]",&query);

            l=strlen(query);

            fp=fopen("contact.dll","r");

            system("cls");

            printf("\n\n..::Search result for '%s' \n===================================================\n",query);

            while(fread(&ct,sizeof(ct),1,fp)==1)

            {

                for(i=0; i<=l; i++)

                    name[i]=ct.name[i];

                name[l]='\0';

                if(stricmp(name,query)==0)

                {

                    printf("\n..::Name\t: %s\n..::Phone\t: %lld\n",ct.name,ct.ph);

                    found++;

                    if (found%4==0)

                    {

                        printf("..::Press any key to continue...");

                        getch();

                    }

                }

            }

            if(found==0)

                printf("\n..::No match found!");

            else

                printf("\n..::%[^\n] match(s) found!",found);

            fclose(fp);

            printf("\n ..::Try again?\n\n\t[1] Yes\t\t[0] No\n\t");

            scanf("%[^\n]",&ch);

        }
        while(ch==1);

        break;

        /* *********************edit contacts************************/
    case 4:

        system("cls");

        fp=fopen("contact.dll","r");

        ft=fopen("temp.dat","w");

        fflush(stdin);

        printf("..::Edit contact\n===============================\n\n\t..::Enter the name of contact to edit:");

        scanf("%[^\n]",name);

        while(fread(&ct,sizeof(ct),1,fp)==1)

        {

            if(stricmp(name,ct.name)!=0)

                fwrite(&ct,sizeof(ct),1,ft);

        }

        fflush(stdin);

        printf("\n\n..::Editing '%s'\n\n",name);

        printf("..::Name(Use identical):");

        scanf("%[^\n]",&ct.name);

        fflush(stdin);

        printf("..::Phone:");

        scanf("%lld",&ct.ph);

        fflush(stdin);

        printf("\n");

        fwrite(&ct,sizeof(ct),1,ft);

        fclose(fp);

        fclose(ft);

        remove("contact.dll");

        rename("temp.dat","contact.dll");

        break;

        /* ********************delete contacts**********************/
	//This case is used for Delete a Contact//
    case 5:

        system("cls");

        fflush(stdin);

        printf("\n\n\t..::DELETE A CONTACT\n\t==========================\n\t..::Enter the name of contact to delete:");

        scanf("%[^\n]",&name);

        fp=fopen("contact.dll","r");

        ft=fopen("temp.dat","w");

        while(fread(&ct,sizeof(ct),1,fp)!=0)

            if (stricmp(name,ct.name)!=0)

                fwrite(&ct,sizeof(ct),1,ft);

        fclose(fp);

        fclose(ft);

        remove("contact.dll");

        rename("temp.dat","contact.dll");

        break;

    default:

        printf("Invalid choice");

        break;

    }

    printf("\n\n\n..::Enter the Choice:\n\n\t[1] Main Menu\t\t[0] Exit\n");

    scanf("%[^\n]",&ch);

    switch (ch)

    {

    case 1:

        goto main;

    case 0:

        break;

    default:

        printf("Invalid choice");

        break;

    }

    return 0;

}//end of main
