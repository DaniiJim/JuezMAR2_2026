# MAR2 — Ejercicios Juez

Repositorio básico para tener **ejercicios de MAR2** organizados por tema:

- **Tema 1:** Programación Dinámica  
- **Tema 2:** Ramificación y Poda  

La idea es mantenerlo simple: compilar y ejecutar los `.cpp` sin necesidad de crear un entorno

---

## Estructura del repo

```text
JUEZMAR2_2026/
├── Prog_Dinamica/
│   ├── 01_CuerdaCometa/
│   │   ├── 01_Cometa.cpp
│   │   ├── datos.txt
│   │   ├── 01_Cometa.exe (opcional: generado al compilar en Windows)
│   │   ├── Matriz.h / EnterosInf.h (headers auxiliares)
│   │   └── prob-...pdf (enunciado)
│   ├── 02_ConstruyendoDianas/
│   ├── 03_Subir/
│   └── ...
├── RyP/
│   ├── 14_.../
│   ├── 15_.../
│   └── ...
├── .gitattributes
└── README.md
```

> Los ejercicios siguen esta estructura: **cada carpeta de ejercicio es “autocontenida”** y suele incluir el `.cpp`, un `datos.txt` para pruebas, los headers auxiliares (`Matriz.h`, `EnterosInf.h`) y el enunciado en PDF.  
> El `.exe` aparece solo si lo has compilado en Windows.


<br>

---

## Compilar y ejecutar

### 1) Compilar

> Normalmente compilas el `.cpp` de la carpeta del ejercicio y te genera un ejecutable  
> (en Windows será `.exe`).

#### Opción rápida (mínima)
Funciona perfectamente para la mayoría de ejercicios:

```bash
g++ <ruta_al_cpp> -o <ejecutable>
```

#### Opción recomendada
No es obligatoria, pero evita diferencias raras entre PCs y te avisa de cosas útiles:

```bash
g++ -std=c++17 -O2 -Wall <ruta_al_cpp> -o <ejecutable>
```

**Ejemplo real (Windows):**

```bash
g++ -std=c++17 -O2 -Wall .\Prog_Dinamica\01_CuerdaCometa\01_Cometa.cpp -o 01_Cometa
```


**Ejemplo real (Linux/macOS):**

```bash
g++ -std=c++17 -O2 -Wall ./Prog_Dinamica/01_CuerdaCometa/01_Cometa.cpp -o 01_Cometa
```

> Nota: si compilas dentro de la propia carpeta del ejercicio, la ruta se acorta muchísimo:
>
> ```bash
> cd Prog_Dinamica/01_CuerdaCometa
> g++ -std=c++17 -O2 -Wall 01_Cometa.cpp -o 01_Cometa
> ```

<br>

### 2) Ejecutar

**Windows:**

```bash
.\<ejecutable>.exe
```

**Linux/macOS:**

```bash
./<ejecutable>
```
