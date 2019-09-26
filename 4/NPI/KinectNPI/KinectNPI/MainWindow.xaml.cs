using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace NPIGrupo7Kinect
{
    /// <summary>
    /// Lógica de interacción para MainWindow [Interfaz gráfica del menú de selección de año y eventos].
    /// </summary>
    public partial class MainWindow : Window
    {
        // Diccionario con los títulos de los eventos de un año
        private Dictionary<int, List<String>> dictionary = new Dictionary<int, List<string>>();

        // Diccionario con la información ampliada de los eventos de un año
        private Dictionary<int, List<String>> extendida = new Dictionary<int, List<string>>();
        private Boolean popupAbierto = false; // Indica si hay un evento abierto
        private Window1 popup; // Ventana del popup
        private int anio_actual; // Año seleccionado actualmente

        // Propiedad para acceder al popupAbierto
        public bool PopupAbierto { get => popupAbierto; set => popupAbierto = value; }
        
        /**
         * Constructor de la ventana principal.
         * Utilizado para rellenar los datos de los diccionarios.
         */
        public MainWindow()
        {
            InitializeComponent();
            dictionary.Add(1996, new List<string> { "Mes de diciembre más lluvioso del siglo", "Elecciones generales 1996", "EL OPALO Y LA SERPIENTE: PREMIO ANDALUCIA DE NOVELA 1996" });
            dictionary.Add(1492, new List<string> { "Toma de Granada", "Descubrimiento de América" });
            dictionary.Add(1936, new List<string> { "Fallecimiento de Federico García Lorca", "Guerra Civil Española"});

            extendida.Add(1996, new List<string> { Properties.Resources.lluvioso, Properties.Resources.elecciones, Properties.Resources.opalo });
            extendida.Add(1492, new List<string> { Properties.Resources.tomaGranada, Properties.Resources.descubrimiento });
            extendida.Add(1936, new List<string> { Properties.Resources.lorca, Properties.Resources.guerra });

            ColocarAño(1996);

            App.setMainWindow(this);

        }

        /**
         * Coloca los evento de un año en la pantalla actual. Se selecciona el elemento en la mitad.
         * @param año Año que se desea 
         */
        private void ColocarAño(int año)
        {
            Año.Content = año;
            Sucesos.Items.Clear();
            foreach(String suceso in dictionary[año])
            {
                Sucesos.Items.Add(suceso);
            }

            Sucesos.SelectedIndex = Sucesos.Items.Count / 2;
            anio_actual = año;
        }

        /**
         * Cambia el evento seleccionado del año.
         * @param movimiento Hacia qué dirección moverse. 1 hacia abajo ó -1 hacia arriba.
         */
        public void CambiarSeleccion(int movimiento)
        {
            this.Dispatcher.Invoke(()=>
            {
                if ((movimiento == 1 && Sucesos.SelectedIndex == Sucesos.Items.Count - 1) ||
                (movimiento == -1 && Sucesos.SelectedIndex == 0))
                {
                    return;
                }

                Sucesos.SelectedIndex += movimiento;
            });
        }
        /**
         * Cambia el año seleccionado.
         * @param movimiento Hacia qué dirección moverse. 1 para pasar al siguiente año con eventos ó -1 al anterior.
         */
        public void PasarAño(int movimiento)
        {
            this.Dispatcher.Invoke(() =>
            {
                var claves = dictionary.Keys.ToList();
                int indice = claves.IndexOf(int.Parse(Año.Content.ToString()));

                int nuevo_indice = (indice + movimiento) % claves.Count;
                if (nuevo_indice == -1) nuevo_indice = claves.Count - 1;
                ColocarAño(claves[nuevo_indice]);

            });
        }

        /**
         * Cambia al año pasado como parámetro.
         * @pre el año pasado debe de tener al menos un evento disponible.
         * @param string_anio String correspondiente al año al que se desea pasar.
         */
        public void IrAño(string string_anio)
        {
            this.Dispatcher.Invoke(() =>
            {
                int anio = int.Parse(string_anio);
                int indice = dictionary.Keys.ToList().IndexOf(anio);

                ColocarAño(dictionary.Keys.ToList()[indice]);

            });
        }

        /**
         * Cambia al evento indicado con los parámetros.
         * @pre El evento ha de existir.
         * @param string_anio String correspondiente al año al que se desea pasar.
         * @param string_pos Posición de la lista del año en la que se encuentra el evento correspondiente
         */
        public void IrEvento(string string_anio, string string_pos)
        {
            this.Dispatcher.Invoke(() =>
            {
                int anio = int.Parse(string_anio);
                int evento = int.Parse(string_pos);

                int indice = dictionary.Keys.ToList().IndexOf(anio);

                if (anio != anio_actual)
                    ColocarAño(dictionary.Keys.ToList()[indice]);
                Sucesos.SelectedIndex = evento;
                abrirPopUp();
            });
        }

        /**
         * Abre la información del evento seleccionado.
         */
        public void abrirPopUp()
        {
            this.Dispatcher.Invoke(() =>
            {
                popupAbierto = true;
                popup = new Window1(Sucesos.SelectedItem.ToString(), extendida[anio_actual][Sucesos.SelectedIndex]);
                popup.Show();
            });

        }

        /**
         * Cierra la información una vez ha sido abierta.
         * @pre La ventana de información debe de estar abierta.
         */
        public void cerrarPopUp()
        {
            this.Dispatcher.Invoke(() =>
            {
                popupAbierto = false;
                popup.Close();
            });
        }

        /**
         * Nos permite avanzar el texto de la información ampliada.
         * @pre La ventana de información debe estar abierta.
         */
        public void subirPopUp()
        {
            this.Dispatcher.Invoke(() =>
            {
                var focus = FocusManager.GetFocusedElement(popup);
                popup.textoPopUp.Focus();
                popup.textoPopUp.ScrollToVerticalOffset(popup.textoPopUp.VerticalOffset+200);
            }
            );
        }

        /**
         * Nos permite retroceder en el texto de la información ampliada.
         * @pre La ventana de información debe estar abierta.
         */
        public void bajarPopUp()
        {
            this.Dispatcher.Invoke(() =>
            {
                var focus = FocusManager.GetFocusedElement(popup);
                popup.textoPopUp.Focus();
                popup.textoPopUp.ScrollToVerticalOffset(popup.textoPopUp.VerticalOffset - 200);
            }
            );
        }

        /**
         * Amplia el tamaño de la fuente de la información (lo duplica)
         * @pre La ventana de información debe estar abierta.
         */
        public void Ampliar()
        {
            this.Dispatcher.Invoke(() =>
            {
                popup.Ampliar();
            });
        }

        /**
         * Reduce el tamaño de la fuente de la información (lo reduce a la mitad)
         * @pre La ventana de información debe estar abierta.
         */
        public void Reducir()
        {
            this.Dispatcher.Invoke(() =>
            {
                popup.Reducir();
            });
        }
    }
}
