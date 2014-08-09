#include "time2.h"
#include "function.h"

int time1() {
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if (screen == NULL) {
        fprintf(stderr, "Erro na execucao - screen not created successfully\n");
        return -1;
    }

    // load an image
    SDL_Surface* bmp = NULL;
    SDL_Surface* linha = NULL;
    SDL_Surface* badbmp = NULL;
    SDL_Surface* tardis = NULL;
    SDL_Surface* goodbmp = NULL;

    SDL_Surface * spikeImg[2]; // Vetor de imagens de espinhos
    spikeImg[0] = NULL;
    spikeImg[1] = NULL;

    SDL_Surface * buttonImg[2]; // Vetor de imagens de botoes
    buttonImg[0] = NULL;
    buttonImg[1] = NULL;
    // SDL_Surface* botao2 = NULL;

    /// Verifica se todas imagens carregadas existem
    if (!initSDL_Surface(&bmp, "img/1.bmp") && !initSDL_Surface(&bmp, "src/img/000.bmp")) { /// Voce tinha posto 0.bmp (mas nao existe tal imagem) - verificar depois
        fprintf(stderr, "Erro na execucao - 0002\n");
        return -1;
    }
    if (!initSDL_Surface(&linha, "img/linha.bmp") && !initSDL_Surface(&linha, "src/img/linha.bmp")) {
        fprintf(stderr, "Erro na execucao - 0003\n");
        return -1;
    }
    if (!initSDL_Surface(&badbmp, "img/1.bmp") && !initSDL_Surface(&badbmp, "src/img/000.bmp")) {
        fprintf(stderr, "Erro na execucao - 0004\n");
        return -1;
    }
    if (!initSDL_Surface(&tardis, "img/tardis.bmp") && !initSDL_Surface(&tardis, "src/img/tardis.bmp")) {
        fprintf(stderr, "Erro na execucao - 0005\n");
        return -1;
    }
    if (!initSDL_Surface(&goodbmp, "img/1.bmp") && !initSDL_Surface(&goodbmp, "src/img/00000.bmp")) {
        fprintf(stderr, "Erro na execucao - 0006\n");
        return -1;
    }
    if (!initSDL_Surface(&spikeImg[0], "img/spikes1.bmp") && !initSDL_Surface(&spikeImg[0], "src/img/spikes1.bmp")) {
        fprintf(stderr, "Erro na execucao - 0007\n");
        return -1;
    }
    if (!initSDL_Surface(&spikeImg[1], "img/spikes2.bmp") && !initSDL_Surface(&spikeImg[1], "src/img/spikes2.bmp")) {
        fprintf(stderr, "Erro na execucao - 0008\n");
        return -1;
    }
    if (!initSDL_Surface(&buttonImg[0], "img/botao1.bmp") && !initSDL_Surface(&buttonImg[0], "src/img/botao1.bmp")) {
        fprintf(stderr, "Erro na execucao - 0009\n");
        return -1;
    }
    if (!initSDL_Surface(&buttonImg[1], "img/botao2.bmp") && !initSDL_Surface(&buttonImg[1], "src/img/botao2.bmp")) {
        fprintf(stderr, "Erro na execucao - 0010\n");
        return -1;
    }

    /// Se continuou todas imagens devem existir

//    b2Vec2 gravity(0, -9.8); //normal earth gravity, 9.8 m/s/s straight down!
//    bool doSleep = true;
//    b2World* myWorld = new b2World(gravity, doSleep);


    SDL_Rect offset;
    set_sdlRect(&offset, 120, PLATAFORMA_Y);

    SDL_Rect grama;
    set_sdlRect(&grama, 0, 350);


    SDL_Rect timespace;
    set_sdlRect(&timespace, 100, 178);

    SDL_Rect inimigo;
    set_sdlRect(&inimigo, 120, PLATAFORMA_Y);

    SDL_Rect amigo;
    set_sdlRect(&amigo, 120, PLATAFORMA_Y);

    SDL_Rect espinhos[2];

    set_sdlRect(&espinhos[0], 400, 138);
    set_sdlRect(&espinhos[1], 416, 98);

    SDL_Rect botao[2];

    set_sdlRect(&botao[0], 30, 330);

    set_sdlRect(&botao[1], 210, 330);

    int q, ger, i, p, espelho, reg, grav, start, m, r, s;
    int lado, startrad, rad, mirror, u, graviole, l, nap;

    int *click = (int *) calloc(13, sizeof (int));

    click = init_click(click);

    int cont = 0;

    int vetor[10000];
    vetor[0] = 0;
    start = 0;
    startrad = 0;
    lado = 0;
    reg = 0;
    grav = 0;
    i = 0; //o nÃºmero de i tem que ser par, e metade do valor + 1 serÃ¡ a diferenÃ§a
    p = 0;
    q = 0;
    r = 0;
    s = 0;
    l = 0;
    m = 0;
    ger = 0;
    espelho = 0;
    mirror = 0;

    bool done = false;
    while (!done) {
        //Get the keystates
        Uint8 *keystates = SDL_GetKeyState(NULL);
        if (offset.y >= PLATAFORMA_Y) {
            delay(0.01);

            cont = 0;
        }


        if (keystates[ SDLK_LEFT ]) { //If left is pressed
            delay(WAIT);
            click = function_left(&vetor[i], click, &offset, &lado);
            imprimeVariaveisTeste(offset, amigo, inimigo, cont);
        }
        if (keystates[ SDLK_RIGHT ]) { //If right is pressed
            delay(WAIT);
            click = function_right(&vetor[i], click, &offset, &lado);
            imprimeVariaveisTeste(offset, amigo, inimigo, cont);
        }

        //Update the screen
        if (SDL_Flip(screen) == -1) {
            return 1;
        }

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            p++;
            i++;
            vetor[i] = 0;
            switch (event.type) {
                case SDL_QUIT:
                    done = true;
                    break;

                case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            click = function_up(&vetor[i], click, &offset, lado, isAbleToJump(&cont));
                            imprimeVariaveisTeste(offset, amigo, inimigo, cont);
                            break;

                        case SDLK_DOWN:
                            function_down(&vetor[i]);
                            imprimeVariaveisTeste(offset, amigo, inimigo, cont);
                            break;

                        case SDLK_ESCAPE:
                            function_exit(&done);
                            break;

                        default:
                            break;

                    }
                }
            }

        }
        if (offset.y < PLATAFORMA_Y) {
            if (reg == 15) {
                offset.y += 15;
                reg = 0;
            }
            if (reg < 15) {
                reg++;
            }
        }

        if (vetor[i] >= 20) {
            start++;
        }
        if (start == 1) {
            l = i;
            m = i;
        }
        if (start == 5) {
            inimigo.x = 120;
            inimigo.y = PLATAFORMA_Y;
            q = 0;
        }
        if (start > 0) {
            if (ger == 5) {
                ger = 0;
                q = q + 1;
                if (q < l) {
                    if (vetor[q] == 0) {
                        inimigo.x = inimigo.x;
                    }
                    if (vetor[q] == 4) {
                        espelho = 1;
                        if (inimigo.y < PLATAFORMA_Y) {
                            click[5] = -1;
                            click[4] = -1;
                            click[6] = -1;
                            click[7]++;
                            inimigo.x -= 10;
                        }
                        if (inimigo.y >= PLATAFORMA_Y) {
                            click[5]++;
                            click[4] = -1;
                            click[6] = -1;
                            click[7] = -1;
                            inimigo.x -= 10;
                        }
                    }
                    if (vetor[q] == 3) {
                        espelho = 2;

                        if (inimigo.y < PLATAFORMA_Y) {
                            click[5] = -1;
                            click[4] = -1;
                            click[7] = -1;
                            click[6]++;
                            inimigo.x += 10;
                        }
                        if (inimigo.y >= PLATAFORMA_Y) {
                            click[4]++;
                            click[5] = -1;
                            click[6] = -1;
                            click[7] = -1;
                            inimigo.x += 10;
                        }
                    }
                    if (vetor[q] == 1) {
                        if (espelho == 2) {
                            inimigo.y = inimigo.y - 20;
                            click[4] = -1;
                            click[5] = -1;
                            click[6]++;
                            click[7] = -1;
                        }
                        if (espelho == 1) {
                            inimigo.y -= 20;
                            click[4] = -1;
                            click[5] = -1;
                            click[7]++;
                            click[6] = -1;
                        }
                    }
                }
                if (q > m) {
                    click[4] = -1;
                    click[5] = -1;
                    click[6] = -1;
                    click[7] = -1;
                    inimigo.y = 600;
                    inimigo.x = 1000;
                }
            }
        }
        if (ger < 5) {
            ger++;
        }

        if (vetor[i] == 2) {
            startrad++;

            if (startrad == 1) {
                amigo.x = offset.x;
                amigo.y = offset.y;
            }
        }
        if (startrad > 5) {
            if (startrad == 6) {
                nap = i;
                startrad++;
            }

            if (rad == 5) {
                rad = 0;
                u = l;
                l++;

                if (u < nap) {
                    if (vetor[u] == 4) {
                        mirror = 1;
                        if (amigo.y < PLATAFORMA_Y) {
                            click[9] = -1;
                            click[8] = -1;
                            click[10] = -1;
                            click[11]++;
                            amigo.x -= 10;
                        }

                        if (amigo.y >= PLATAFORMA_Y) {
                            click[9]++;
                            click[8] = -1;
                            click[10] = -1;
                            click[11] = -1;
                            amigo.x -= 10;
                        }
                    }

                    if (vetor[u] == 3) {
                        mirror = 2;

                        if (amigo.y < PLATAFORMA_Y) {
                            click[9] = -1;
                            click[8] = -1;
                            click[11] = -1;
                            click[10]++;
                            amigo.x += 10;
                        }
                        if (amigo.y >= PLATAFORMA_Y) {
                            click[8]++;
                            click[9] = -1;
                            click[10] = -1;
                            click[11] = -1;
                            amigo.x += 10;
                        }
                    }
                    if (vetor[u] == 1) {
                        if (mirror == 2) {
                            amigo.y -= 20;
                            click[8] = -1;
                            click[9] = -1;
                            click[10]++;
                            click[11] = -1;
                        }

                        if (mirror == 1) {
                            amigo.y -= 20;
                            click[8] = -1;
                            click[9] = -1;
                            click[11]++;
                            click[10] = -1;
                        }
                    }

                }
            }
        }
        if (u > nap) {
            click[8] = -1;
            click[9] = -1;
            click[10] = -1;
            click[11] = -1;
            amigo.y = 20;
            amigo.x = 2000;
        }

        if (rad < 5) {
            rad++;
        }

        if (inimigo.y < PLATAFORMA_Y) {
            if (grav == 15) {
                inimigo.y += 10;
                grav = 0;
            }
            if (grav < 15) {
                grav++;
            }
        }

        if (amigo.y < PLATAFORMA_Y && startrad > 5) {
            if (graviole == 15) {
                amigo.y += 10;
                graviole = 0;
            }
            if (graviole < 15) {
                graviole++;
            }
        }
        if (offset.x == 20 && offset.y == PLATAFORMA_Y) {
            r++;
            if (r < 2) {
                click[12]++;
            }
        }

        if (inimigo.x == 20 && inimigo.y == PLATAFORMA_Y) {
            r++;
            if (r < 2) {
                click[12]++;
            }
        }

        if (amigo.x == 20 && amigo.y == PLATAFORMA_Y) {
            r++;
            if (r < 2) {
                click[12]++;
            }
        }

        if (offset.x == 200 && offset.y == PLATAFORMA_Y) {
            s++;
            if (s < 2) {
                click[12]++;
            }
        }

        if (inimigo.x == 200 && inimigo.y == PLATAFORMA_Y) {
            s++;
            if (s < 2) {
                click[12]++;
            }
        }

        if (amigo.x == 200 && amigo.y == PLATAFORMA_Y) {
            s++;
            if (s < 2) {
                click[12]++;
            }
        }

        if (q > 0 && (offset.x == inimigo.x && offset.y == inimigo.y)) {
            free(click);
            return 0;
        }


        if (u > 0 && ((offset.x == amigo.x && offset.y == amigo.y) || (inimigo.x == amigo.x && inimigo.y == amigo.y))) {
            free(click);
            return 0;
        }


        // DRAWING STARTS HERE
        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 255));

        // draw bitmap
        SDL_BlitSurface(linha, 0, screen, &grama);
        SDL_BlitSurface(tardis, 0, screen, &timespace);
        Uint32 colorkey = SDL_MapRGB(tardis->format, 255, 255, 255);
        SDL_SetColorKey(tardis, SDL_SRCCOLORKEY, colorkey);

        if (click[12] % 4 == 0) {
            if (offset.x > 375) {
                if (offset.y > 70) {
                    free(click);
                    return 0;
                }
            }

            SDL_Surface* spike1 = SDL_LoadBMP("img/spikes1.bmp");
            SDL_SetColorKey(spike1, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(spike1, 0, screen, &espinhos[0]);

        }

        if (click[12] % 4 == 1) {
            if (offset.x > 375) {
                if (offset.y > 70) {
                    free(click);
                    return 0;
                }
            }
            SDL_Surface* spike1 = SDL_LoadBMP("img/spikes1.bmp");
//            SDL_SetColorKey(spike1, SDL_SRCCOLORKEY, colorkey);
            SDL_SetColorKey(spike1, SDL_TRUE, SDL_MapRGB(spike1->format, 0, 0xFF, 0xFF ) );
            SDL_BlitSurface(spike1, 0, screen, &espinhos[0]);
        }
        SDL_Surface* spike2 = SDL_LoadBMP("img/spikes2.bmp");
        SDL_SetColorKey(spike2, SDL_SRCCOLORKEY, colorkey);
        SDL_BlitSurface(spike2, 0, screen, &espinhos[1]);

        SDL_Surface* botao1 = SDL_LoadBMP("img/botao1.bmp");
        SDL_SetColorKey(botao1, SDL_SRCCOLORKEY, colorkey);
        SDL_BlitSurface(botao1, 0, screen, &botao[0]);

        SDL_Surface* botao2 = SDL_LoadBMP("img/botao2.bmp");
        SDL_SetColorKey(botao2, SDL_SRCCOLORKEY, colorkey);
        SDL_BlitSurface(botao2, 0, screen, &botao[1]);


        if (click[0] % 4 == 0) {
            SDL_Surface* bmp = SDL_LoadBMP("img/1.bmp");
            Uint32 colorkey = SDL_MapRGB(bmp->format, 255, 255, 255);
            SDL_SetColorKey(bmp, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(bmp, 0, screen, &offset);
        }

        if (click[0] % 4 == 1) {
            SDL_Surface* bmp = SDL_LoadBMP("img/2.bmp");
            Uint32 colorkey = SDL_MapRGB(bmp->format, 255, 255, 255);
            SDL_SetColorKey(bmp, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(bmp, 0, screen, &offset);
        }

        if (click[0] % 4 == 2) {
            SDL_Surface* bmp = SDL_LoadBMP("img/3.bmp");
            Uint32 colorkey = SDL_MapRGB(bmp->format, 255, 255, 255);
            SDL_SetColorKey(bmp, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(bmp, 0, screen, &offset);
        }
        if (click[0] % 4 == 3) {
            SDL_Surface* bmp = SDL_LoadBMP("img/4.bmp");
            Uint32 colorkey = SDL_MapRGB(bmp->format, 255, 255, 255);
            SDL_SetColorKey(bmp, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(bmp, 0, screen, &offset);
        }

        if (click[1] % 4 == 0) {
            SDL_Surface* bmp = SDL_LoadBMP("img/5.bmp");
            Uint32 colorkey = SDL_MapRGB(bmp->format, 255, 255, 255);
            SDL_SetColorKey(bmp, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(bmp, 0, screen, &offset);
        }
        if (click[1] % 4 == 1) {
            SDL_Surface* bmp = SDL_LoadBMP("img/6.bmp");
            Uint32 colorkey = SDL_MapRGB(bmp->format, 255, 255, 255);
            SDL_SetColorKey(bmp, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(bmp, 0, screen, &offset);
        }
        if (click[1] % 4 == 2) {
            SDL_Surface* bmp = SDL_LoadBMP("img/7.bmp");
            Uint32 colorkey = SDL_MapRGB(bmp->format, 255, 255, 255);
            SDL_SetColorKey(bmp, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(bmp, 0, screen, &offset);
        }
        if (click[1] % 4 == 3) {
            SDL_Surface* bmp = SDL_LoadBMP("img/8.bmp");
            Uint32 colorkey = SDL_MapRGB(bmp->format, 255, 255, 255);
            SDL_SetColorKey(bmp, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(bmp, 0, screen, &offset);
        }
        if (click[2] % 2 == 0) {
            SDL_Surface* bmp = SDL_LoadBMP("img/01.bmp");
            Uint32 colorkey = SDL_MapRGB(bmp->format, 255, 255, 255);
            SDL_SetColorKey(bmp, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(bmp, 0, screen, &offset);
        }
        if (click[2] % 2 == 1) {
            SDL_Surface* bmp = SDL_LoadBMP("img/02.bmp");
            Uint32 colorkey = SDL_MapRGB(bmp->format, 255, 255, 255);
            SDL_SetColorKey(bmp, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(bmp, 0, screen, &offset);
        }
        if (click[3] % 2 == 0) {
            SDL_Surface* bmp = SDL_LoadBMP("img/03.bmp");
            Uint32 colorkey = SDL_MapRGB(bmp->format, 255, 255, 255);
            SDL_SetColorKey(bmp, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(bmp, 0, screen, &offset);
        }
        if (click[3] % 2 == 1) {
            SDL_Surface* bmp = SDL_LoadBMP("img/04.bmp");
            Uint32 colorkey = SDL_MapRGB(bmp->format, 255, 255, 255);
            SDL_SetColorKey(bmp, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(bmp, 0, screen, &offset);
        }
        if (q > 0) {
            if (click[4] % 4 == 0) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/1.bmp");
                Uint32 colorkey = SDL_MapRGB(badbmp->format, 255, 255, 255);
                SDL_SetColorKey(badbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(badbmp, 0, screen, &inimigo);
            }

            if (click[4] % 4 == 1) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/2.bmp");
                Uint32 colorkey = SDL_MapRGB(badbmp->format, 255, 255, 255);
                SDL_SetColorKey(badbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(badbmp, 0, screen, &inimigo);
            }

            if (click[4] % 4 == 2) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/3.bmp");
                Uint32 colorkey = SDL_MapRGB(badbmp->format, 255, 255, 255);
                SDL_SetColorKey(badbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(badbmp, 0, screen, &inimigo);
            }
            if (click[4] % 4 == 3) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/4.bmp");
                Uint32 colorkey = SDL_MapRGB(badbmp->format, 255, 255, 255);
                SDL_SetColorKey(badbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(badbmp, 0, screen, &inimigo);
            }
            if (click[5] % 4 == 0) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/5.bmp");
                Uint32 colorkey = SDL_MapRGB(badbmp->format, 255, 255, 255);
                SDL_SetColorKey(badbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(badbmp, 0, screen, &inimigo);
            }
            if (click[5] % 4 == 1) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/6.bmp");
                Uint32 colorkey = SDL_MapRGB(badbmp->format, 255, 255, 255);
                SDL_SetColorKey(badbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(badbmp, 0, screen, &inimigo);
            }
            if (click[5] % 4 == 2) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/7.bmp");
                Uint32 colorkey = SDL_MapRGB(badbmp->format, 255, 255, 255);
                SDL_SetColorKey(badbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(badbmp, 0, screen, &inimigo);
            }
            if (click[5] % 4 == 3) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/8.bmp");
                Uint32 colorkey = SDL_MapRGB(badbmp->format, 255, 255, 255);
                SDL_SetColorKey(badbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(badbmp, 0, screen, &inimigo);
            }
            if (click[6] % 2 == 0) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/01.bmp");
                Uint32 colorkey = SDL_MapRGB(badbmp->format, 255, 255, 255);
                SDL_SetColorKey(badbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(badbmp, 0, screen, &inimigo);
            }
            if (click[6] % 2 == 1) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/02.bmp");
                Uint32 colorkey = SDL_MapRGB(badbmp->format, 255, 255, 255);
                SDL_SetColorKey(badbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(badbmp, 0, screen, &inimigo);
            }
            if (click[7] % 2 == 0) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/03.bmp");
                Uint32 colorkey = SDL_MapRGB(badbmp->format, 255, 255, 255);
                SDL_SetColorKey(badbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(badbmp, 0, screen, &inimigo);
            }
            if (click[7] % 2 == 1) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/04.bmp");
                Uint32 colorkey = SDL_MapRGB(badbmp->format, 255, 255, 255);
                SDL_SetColorKey(badbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(badbmp, 0, screen, &inimigo);
            }
        }

        if (u > 0) {
            if (click[8] % 4 == 0) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/1.bmp");
                Uint32 colorkey = SDL_MapRGB(goodbmp->format, 255, 255, 255);
                SDL_SetColorKey(goodbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(goodbmp, 0, screen, &amigo);
            }
            if (click[8] % 4 == 1) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/2.bmp");
                Uint32 colorkey = SDL_MapRGB(goodbmp->format, 255, 255, 255);
                SDL_SetColorKey(goodbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(goodbmp, 0, screen, &amigo);
            }
            if (click[8] % 4 == 2) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/3.bmp");
                Uint32 colorkey = SDL_MapRGB(goodbmp->format, 255, 255, 255);
                SDL_SetColorKey(goodbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(goodbmp, 0, screen, &amigo);
            }
            if (click[8] % 4 == 3) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/4.bmp");
                Uint32 colorkey = SDL_MapRGB(goodbmp->format, 255, 255, 255);
                SDL_SetColorKey(goodbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(goodbmp, 0, screen, &amigo);
            }
            if (click[9] % 4 == 0) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/5.bmp");
                Uint32 colorkey = SDL_MapRGB(goodbmp->format, 255, 255, 255);
                SDL_SetColorKey(goodbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(goodbmp, 0, screen, &amigo);
            }
            if (click[9] % 4 == 1) {
                SDL_Surface *goodbmp = SDL_LoadBMP("img/6.bmp");
                Uint32 colorkey = SDL_MapRGB(goodbmp->format, 255, 255, 255);
                SDL_SetColorKey(goodbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(goodbmp, 0, screen, &amigo);
            }
            if (click[9] % 4 == 2) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/7.bmp");
                Uint32 colorkey = SDL_MapRGB(goodbmp->format, 255, 255, 255);
                SDL_SetColorKey(goodbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(goodbmp, 0, screen, &amigo);
            }
            if (click[9] % 4 == 3) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/8.bmp");
                Uint32 colorkey = SDL_MapRGB(goodbmp->format, 255, 255, 255);
                SDL_SetColorKey(goodbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(goodbmp, 0, screen, &amigo);
            }
            if (click[10] % 2 == 0) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/01.bmp");
                Uint32 colorkey = SDL_MapRGB(goodbmp->format, 255, 255, 255);
                SDL_SetColorKey(goodbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(goodbmp, 0, screen, &amigo);
            }
            if (click[10] % 2 == 1) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/02.bmp");
                Uint32 colorkey = SDL_MapRGB(goodbmp->format, 255, 255, 255);
                SDL_SetColorKey(goodbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(goodbmp, 0, screen, &amigo);
            }
            if (click[11] % 2 == 0) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/03.bmp");
                Uint32 colorkey = SDL_MapRGB(goodbmp->format, 255, 255, 255);
                SDL_SetColorKey(goodbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(goodbmp, 0, screen, &amigo);
            }
            if (click[11] % 2 == 1) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/04.bmp");
                Uint32 colorkey = SDL_MapRGB(goodbmp->format, 255, 255, 255);
                SDL_SetColorKey(goodbmp, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(goodbmp, 0, screen, &amigo);
            }
        }

        SDL_Flip(screen);
    }
    int j;
    for (j = 0; j < i; j++) {
        printf("\n%d", vetor[j]);
    }

    freeSDL_Surface(&bmp);
    freeSDL_Surface(&tardis);
    freeSDL_Surface(&badbmp);
    freeSDL_Surface(&goodbmp);
    freeSDL_Surface(&spikeImg[0]);
    freeSDL_Surface(&spikeImg[1]);
    freeSDL_Surface(&buttonImg[0]);
    freeSDL_Surface(&buttonImg[1]);
    bmp = NULL;
    tardis = NULL;
    badbmp = NULL;
    goodbmp = NULL;
    spikeImg[0] = NULL;
    spikeImg[1] = NULL;
    buttonImg[0] = NULL;
    buttonImg[1] = NULL;

//    delete myWorld;

    free(click);
    return 1;
}
