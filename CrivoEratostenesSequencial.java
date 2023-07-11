
// Código criado para realizar o Problema Crivo de Eratostenes

public class CrivoEratostenesSequencial {
    public static void main(String args[]) {
        long tempo1, tempo2;

        tempo1 = System.currentTimeMillis();
        boolean[] primos = crivoEratostenes(10000);
        mostrarPrimos(primos);
        tempo2 = System.currentTimeMillis();

        System.out.println("\nTempo de execucao: " + (tempo2 - tempo1) + "ms");
    }

    private static boolean[] crivoEratostenes(int n) {
        boolean[] primos = new boolean[n + 1];

        for(int i = 2; i <= n; i++) {
            primos[i] = true;
        }

        for(int i = 2; i <= Math.sqrt(n); i++) {
            if(primos[i]) {
                for(int j = i; j * i <= n; j++) {
                    primos[i * j] = false;
                }
            }
        }


        return primos;
    }

    private static void mostrarPrimos(boolean[] primos) {
        int qntPrimos = 0;
        for(int i = 2; i < primos.length; i++) {
            if(primos[i]) {
                qntPrimos = qntPrimos + 1;
                System.out.printf("%d ", i);
            }
        }
  
        System.out.println("\nQuantidade de Primos: " + qntPrimos);
    }
}
