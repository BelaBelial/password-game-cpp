
# Password Guessing Game In C++ (Jogo de Adivinhação da Senha em C++)
> *Feito apenas para fins educacionais*

### Instruções Básicas De Jogo:
- Inicialmente, é dado a quantidade de caracteres (mínimo 3, máximo 9) de uma senha especial a ser adivinhada.
- As senhas não possuem caracteres especiais, letras maiúsculas ou números. Além disso não formam palavras reais no dicionário, sendo uma sequência aleatória de letras.
- Com cada palpite do usuário, ele recebe de volta algumas informações como: quantidade de letras corretas, corretas e no lugar certo e corretas e no lugar errado.
- A partir disso deve-se adivinhar a senha, quando você acerta, você ganha, não tendo limite de palpites.

## Como O Gerador Da Senha Foi Programado:
*A técnica usada para realizar este processo não foi a técnica mais moderna, sendo mais "old fashioned" quando comparada com as formas mais recentes existentes de gerar números/caracteres aleatórios, tal como as funcões do cabeçalho `<random>`. Abaixo estão as explicações sobre a implementação da técnica:*
- **Ao invés disso, utilizei bibliotecas mais herdadas do C, usadas quando se quer gerar dados aleatórios. Essas são: `<cstdlib>` e `<chrono>`.**

- De início, declarei uma string constante contendo todas as letras minúsculas do alfabeto, descartando o **Ç**.

- A ideia geral, foi que eu gerei um número primeiramente, vamos chamar ele de `N`, que corresponderia ao tamanho da senha (quantidade de caracteres), e iria de 3 a 9. A partir desse número, eu gerei outros N número que iriam de 0 até a quantidade de caracteres da string constante menos 1, que havia sido criada anteriormente. Cada um desses N números correspondeu a uma posicão na string, que se traduz para uma letra.

- A partir dos N números, eu indexei a string do alfabeto na posiçao de cada um deles, e peguei o caracter que estava naquela posição, e inseri na string da senha, para formá-la. E assim obtive a senha.

- **Para gerar números, seguindo o fluxo acima, foram usadas técnicas referentes aos cabeçalhos importados. (Toda a abordagem não é a mais atualizada, porém é a que eu mais gostei de trabalhar).**

- **O computador não consegue a partir do nada gerar um número aleatório sem referência prévia. Então é necessário gerar uma *seed* que seria basicamente um número muito grande que representa um ponto de partida, uma posição para indicar para o computador de onde ele pode começar a percorrer a aleatoriedade de gerar números.**

- *Há várias formas de gerar essa **seed**, e uma prática muito comum de fazer isso em qualquer abordagem de qualquer linguagem para qualquer fim, é usar o Tempo Unix.*

- **O Tempo Unix corresponde ao tempo que passou desde o dia 1/1/1970 até o instante atual. Normalmente é feito isso em segundos (número grande que representa a quantidade de segundos que se passou daquela data até o tempo atual, o tipo é `unsigned int`).**

- **Mas eu precisava de algo mais rápido que isso, algo que atualizava mais rápido, porque eu ia gerar N números com um for loop, e a cada iteração que eu teria que fazer, a seed tinha que se atualizar. Porém o for loop é capaz de rodar 15 vezes em menos de 1 milissegundo até.**

- **Então, o que eu fiz foi gerar uma seed que calcula em nanossegundos o tempo que se passou desde o Tempo Unix, pegando o horário atual na minha máquina, e fazendo uma conversão para um número que nao estoure o limite de armazenamento (unsigned int) e para milissegundos. Tudo isso é possível devido ao uso do módulo `<chronos>`, que garante precisão nesse quesito.**

- A seed só precisa ser gerada uma fez, no início da função, cada vez que vai se criar uma nova senha. Ela não precisa por exemplo ser gerada dentro de cada iteração do for loop, porque o que se encarrega de "andar para frente" sozinho na escolha dos números aleatórios sem repetições seguidas é o `rand()`. 

- **Mas como ele faz isso?**
    - A seed, só escolhe o ponto de partida, o começo de um array infindável de combinações numéricas. Então ela apenas coloca o gerador em uma posição inicial baseada no tempo real.
    - O `rand` dá um passo a frente, ele lê o número atual (onde estou atualmente na geração) e da um passo para o próximo bloco de número. 
    - Então o `rand` tem que guardar que ele avançou uma posição. E ele faz isso por meio de uma variável global oculta chamada `next`, que é basicamente uma seed interna. 
    - Logo, a cada "passo" que o `rand()` da para gerar números diferentes, essa variável `next` se atualiza por meio de cálculos matemáticos para chegar na posição atual. 

$\rightarrow$ **E assim são gerados números, construindo a string senha. Eu optei por fazer assim, mas sei que existem outros métodos mais straightforward que fariam meu código possivelmente parecer overengineering. Mas gostei de trabalhar com esses módulos para ganhar experiência.**

> *Project Made and Curated By BelaBelial*