using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Text;
using Microsoft.Kinect;
using Microsoft.Speech.AudioFormat;
using Microsoft.Speech.Recognition;
using System.Speech;
using System.Runtime.InteropServices;
using System.Windows.Documents;
using System.IO;

namespace NPIGrupo7Kinect
{
    /// <summary>
    /// Contiene la lógica que corresponde a la aplicación en general.
    /// En esta clase se activa la Kinect tanto para reconocimiento de gestos como de voz.
    /// </summary>
    public partial class App : Application
    {

        // Tenemos una variable por gesto disponible
        static WaveGesture _gesture = new WaveGesture();
        static WaveGestureLeft _gestureLeft = new WaveGestureLeft();
        static UpGesture _gestureUp = new UpGesture();
        static DownGesture _gestureDown = new DownGesture();
        static CloseFistGesture _gestureCloseFist = new CloseFistGesture();
        static LeftCloseFistGesture _gestureLeftCloseFist = new LeftCloseFistGesture();
        static ZoomInGesture _gestureZoomIn = new ZoomInGesture();
        static ZoomOutGesture _gestureZoomOut = new ZoomOutGesture();
        // Sensor de la Kinect
        static KinectSensor sensor;
        static MultiSourceFrameReader reader;
        // Ventana principal [Visual]
        static MainWindow window;
        // Reconocimiento de voz
        private KinectAudioStream convertStream;
        private SpeechRecognitionEngine speechEngine;

        /**
         * Constructor. Incializa los sensores usados con los datos pertinentes
         */
        App()
        {
            // 1. Recogemos el sensor de la Kinect
            sensor = KinectSensor.GetDefault();

            if (sensor != null)
            {
                // 2. Si lo encontramos lo abrimos
                sensor.Open();
                // 2.1 Recogemos el canal de voz de la Kinect
                IReadOnlyList<AudioBeam> AudioBeamList = sensor.AudioSource.AudioBeams;
                System.IO.Stream AudioStream = AudioBeamList[0].OpenInputStream();
                convertStream = new KinectAudioStream(AudioStream);
                RecognizerInfo Ri = TryGetKinectRecognizer();
                // 2.2 Si podemos reconocer en el idioma deseado
                if (Ri != null)
                {
                    // 2.3 Creamos el motor de reconocimiento y cargamos la gramática de voz propuesta en el XML.
                    this.speechEngine = new SpeechRecognitionEngine(Ri.Id);
                    using (var memoryStream= new MemoryStream(Encoding.ASCII.GetBytes(NPIGrupo7Kinect.Properties.Resources.XMLSpeech)))
                    {
                        var g = new Grammar(memoryStream);
                        this.speechEngine.LoadGrammar(g);
                    }
                    // 2.4 Añadimos la función SpeechRecognized de esta clase a las que se llaman
                    // cuando se detecta un patrón correcto
                    this.speechEngine.SpeechRecognized += this.SpeechRecognized;
                    // 2.5 Añadimos la función SpeechRecognitionRejected de esta clase a las que se llaman
                    // cuando no se puede detectar un patrón correcto
                    this.speechEngine.SpeechRecognitionRejected += this.SpeechRejected;

                    // 2.6 Activamos el canal de escucha e indicamos el formato de reconocimiento deseado
                    this.convertStream.SpeechActive = true;
                    this.speechEngine.SetInputToAudioStream(this.convertStream, new SpeechAudioFormatInfo(EncodingFormat.Pcm, 16000, 16, 1, 32000, 2, null));
                    // 2.7 Activamos el reconocimiento asíncrono para múltiples mensajes.
                    this.speechEngine.RecognizeAsync(RecognizeMode.Multiple);
                }
                else
                {
                    Console.WriteLine("El reconocedor de voz no está operativo.");
                }

                // 3. Abrimos los canles de lectura de imagen para reconocer gestos.
                reader = sensor.OpenMultiSourceFrameReader(FrameSourceTypes.Color | FrameSourceTypes.Depth | FrameSourceTypes.Infrared | FrameSourceTypes.Body);
                reader.MultiSourceFrameArrived += Sensor_SkeletonFrameReady;

                // 3.1 A todos los gestos les añadimos el mismo callback para 
                //     el evento en el que se ha reconocido dicho gesto
                _gesture.GestureRecognized += Gesture_GestureRecognized;
                _gestureLeft.GestureRecognized += Gesture_GestureRecognized;
                _gestureUp.GestureRecognized += Gesture_GestureRecognized;
                _gestureDown.GestureRecognized += Gesture_GestureRecognized;
                _gestureCloseFist.GestureRecognized += Gesture_GestureRecognized;
                _gestureZoomIn.GestureRecognized += Gesture_GestureRecognized;
                _gestureZoomOut.GestureRecognized += Gesture_GestureRecognized;
                _gestureLeftCloseFist.GestureRecognized += Gesture_GestureRecognized;
            }

        }

        /**
         * Callback usado cuando se ha reconocido un mensaje de voz.
         * @param sender Objeto que llama al callback.
         * @param s Parámetros del mensaje reconozido.
         */
        private void SpeechRecognized(object sender, SpeechRecognizedEventArgs s)
        {
            if (s.Result == null) return;

            // Sólo admitimos mensajes de los que se está seguro al 90 % por lo menos
            const double confidenceThreshold = 0.9;
            
            if(s.Result.Confidence > confidenceThreshold)
            {
                // Si es null hemos usado varios parámetros distintos para guardar información.
                // Cuando hay varios suele ser usado para las acciones más complejas como ir al año X.
                if(s.Result.Semantics.Value == null)
                {
                    if(s.Result.Semantics["accion"].Value.ToString() == "RECONOCER")
                    {
                        Console.WriteLine("Vamos al año " + s.Result.Semantics["year"].Value.ToString());
                        window.IrAño(s.Result.Semantics["year"].Value.ToString());
                    }else if(s.Result.Semantics["accion"].Value.ToString() == "INFORMACION")
                    {
                        Console.WriteLine("Visualizamos el evento " + s.Result.Semantics["pos"].Value.ToString());
                        window.IrEvento(s.Result.Semantics["year"].Value.ToString(), s.Result.Semantics["pos"].Value.ToString());
                    }
                }else // En otro caso son las equivalentes orales a la gestión de los gestos
                    switch (s.Result.Semantics.Value.ToString())
                    {
                        case "AMPLIAR":
                            if (window.PopupAbierto)
                                window.Ampliar();
                            Console.WriteLine("Ampliar");
                            break;
                        case "REDUCIR":
                            if (window.PopupAbierto)
                                window.Reducir();
                            Console.WriteLine("Reducir");
                            break;
                        case "ABRIR":
                            if (!window.PopupAbierto)
                                window.abrirPopUp();
                            break;
                        case "CERRAR":
                            if(window.PopupAbierto)
                                window.cerrarPopUp();
                            break;
                        case "ARRIBA":
                            window.CambiarSeleccion(-1);
                            Console.WriteLine("Subir mano");
                            break;
                        case "ABAJO":
                            window.CambiarSeleccion(1);
                            Console.WriteLine("Bajar mano");
                            break;
                        case "IZQUIERDA":
                            window.PasarAño(-1);
                            Console.WriteLine("Deslizar mano derecha");
                            break;
                        case "DERECHA":
                            window.PasarAño(1);
                            Console.WriteLine("Deslizar mano derecha");
                            break;
                    }
            }
        }

        /**
         * Callback si no se detecta una frase válida [NO USADO]
         */
        private void SpeechRejected(object sender, SpeechRecognitionRejectedEventArgs s)
        {
            
        }

        /** 
         * Método que comrpueba si existe un modo de reconocimiento en Kinect con el lenguaje deseado.
         * @return El reconoceder si hay uno válido o null si no hay ninguno válido.
         */
        private static RecognizerInfo TryGetKinectRecognizer()
        {
            IEnumerable<RecognizerInfo> Recognizers;
            try
            {
                Recognizers = SpeechRecognitionEngine.InstalledRecognizers();
            }catch (COMException)
            {
                return null;
            }
            foreach(RecognizerInfo Recognizer in Recognizers)
            {
                
                string value;
                Recognizer.AdditionalInfo.TryGetValue("Kinect", out value);
                if("True".Equals(value, StringComparison.OrdinalIgnoreCase) && "es-ES".Equals(Recognizer.Culture.Name, StringComparison.OrdinalIgnoreCase))
                {
                    return Recognizer;
                }
            }
            return null;
        }

        /**
         * Calcula la longitud de un vector con respecto a la cámra.
         * @param point Punto en el espacio relativo a la cámara.
         * @return Distancia entre la camára y el punto proporcionado.
         */
        private static double VectorLength(CameraSpacePoint point)
        {
            var result = Math.Pow(point.X, 2) + Math.Pow(point.Y, 2) + Math.Pow(point.Z, 2);

            result = Math.Sqrt(result);

            return result;
        }

        /**
         * Obtiene el cuerpo más cercano a la cámara.
         * @param bodyFrame Frame con todos los cuerpos de la imagen.
         * @return Cuerpo más cercano a la cámara.
         */
        private static Body FindClosestBody(BodyFrame bodyFrame)
        {
            Body result = null;
            double closestBodyDistance = double.MaxValue;

            Body[] bodies = new Body[bodyFrame.BodyCount];
            bodyFrame.GetAndRefreshBodyData(bodies);

            foreach (var body in bodies)
            {
                if (body.IsTracked)
                {
                    var currentLocation = body.Joints[JointType.SpineBase].Position;

                    var currentDistance = VectorLength(currentLocation);

                    if (result == null || currentDistance < closestBodyDistance)
                    {
                        result = body;
                        closestBodyDistance = currentDistance;
                    }
                }
            }

            return result;
        }

        /**
         * Callback que se produce cuando se detecta un frame de cuerpo válido.
         * Llama a los Update de los gestos para que puedan actualizarse en caso de que alguno se esté produciendo.
         * @param sender Objeto que llama al callback.
         * @return e Evento de detección del frame
         */
        static void Sensor_SkeletonFrameReady(object sender, MultiSourceFrameArrivedEventArgs e)
        {
            try {
                var reference = e.FrameReference.AcquireFrame();
                using (var frame = reference.BodyFrameReference.AcquireFrame())
                {
                    if (frame != null)
                    {

                        Body body = FindClosestBody(frame);

                        if (body != null)
                        {
                            _gesture.Update(body);
                            _gestureLeft.Update(body);
                            _gestureUp.Update(body);
                            _gestureDown.Update(body);
                            _gestureCloseFist.Update(body);
                            _gestureZoomIn.Update(body);
                            _gestureZoomOut.Update(body);
                            _gestureLeftCloseFist.Update(body);
                        }
                    }
                }
            }
            catch (System.InvalidOperationException )
            {

            }
            
        }

        /**
         * Callback que se produce cuando se ha detectado un gesto válido.
         * Dependiendo del objeto que llame, que será una instancia de la clase
         * de un gesto, realizaremos la acción correspondiente.
         * @param sender Objeto que llama al callback.
         * @e Argumentos del evento.
         */
        static void Gesture_GestureRecognized(object sender, EventArgs e)
        {
            if (sender is WaveGesture)
            {
                window.PasarAño(-1);
                Console.WriteLine("Deslizar mano derecha");
            }
            else if (sender is WaveGestureLeft)
            {
                window.PasarAño(1);
                Console.WriteLine("Deslizar mano izquierda");
            }
            else if (sender is UpGesture)
            {
                if (window.PopupAbierto)
                {
                    window.subirPopUp();
                }
                else
                {
                    window.CambiarSeleccion(-1);
                    Console.WriteLine("Subir mano");
                }
            }
            else if (sender is DownGesture)
            {
                if (window.PopupAbierto)
                {
                    window.bajarPopUp();
                }
                else
                {
                    window.CambiarSeleccion(1);
                    Console.WriteLine("Bajar mano");
                }
            }
            else if (sender is CloseFistGesture)
            {
                if (window.PopupAbierto)
                    window.cerrarPopUp();
                else
                    window.abrirPopUp();
                Console.WriteLine("Cerrar puño");
            }
            else if (sender is ZoomInGesture)
            {
                if (window.PopupAbierto)
                    window.Ampliar();
                Console.WriteLine("Ampliar");
            }
            else if (sender is ZoomOutGesture)
            {
                if (window.PopupAbierto)
                    window.Reducir();
                Console.WriteLine("Reducir");
            }
            else if (sender is LeftCloseFistGesture)
            {
                Console.WriteLine("Cerrar puño izquierdo");
            }
        }

        /**
         * Modifcador del atributo ventana principal
         * @param thewindow Ventana principal a asignar
         */
        static public void setMainWindow(MainWindow thewindow)
        {
            window = thewindow;
        }

    }
}
