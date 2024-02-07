-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 14-04-2023 a las 19:27:05
-- Versión del servidor: 10.4.27-MariaDB
-- Versión de PHP: 8.2.0

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `practica2`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `categorias`
--

CREATE TABLE `categorias` (
  `id` int(11) NOT NULL,
  `nombre` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `categorias`
--

INSERT INTO `categorias` (`id`, `nombre`) VALUES
(1, 'Arte y antigüedades'),
(2, 'Automóviles y motocicletas'),
(3, 'Electrónica y tecnología'),
(4, 'Moda y accesorios'),
(5, 'Joyería y relojes'),
(6, 'Juguetes y juegos'),
(7, 'Muebles y decoración del hogar'),
(8, 'Instrumentos musicales'),
(9, 'Artículos deportivos y de recreación'),
(10, 'Herramientas y equipos industriales'),
(11, 'Productos de belleza y cuidado personal'),
(12, 'Productos para mascotas'),
(13, 'Libros y cómics'),
(14, 'Equipos de cocina y electrodomésticos'),
(15, 'Otros');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `chats`
--

CREATE TABLE `chats` (
  `id_chat` int(11) NOT NULL,
  `id_subasta_aso` int(11) NOT NULL,
  `id_cliente1` int(11) NOT NULL,
  `id_cliente2` int(11) NOT NULL,
  `fecha` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `imagenes`
--

CREATE TABLE `imagenes` (
  `id_imagen` int(11) NOT NULL,
  `id_subasta` int(11) NOT NULL,
  `ruta` varchar(20) NOT NULL,
  `nombre` varchar(20) NOT NULL,
  `mimeType` varchar(30) NOT NULL,
  `tipoAcceso` tinyint(4) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `imagenes`
--

INSERT INTO `imagenes` (`id_imagen`, `id_subasta`, `ruta`, `nombre`, `mimeType`, `tipoAcceso`) VALUES
(1, 12, '', 'WhatsApp-Image-2021-', 'image/png', 0),
(2, 12, '2.png', 'WhatsApp-Image-2021-', 'image/png', 0),
(3, 14, '3.png', 'WhatsApp-Image-2021-', 'image/png', 0);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `mensajes`
--

CREATE TABLE `mensajes` (
  `id_mensaje` int(11) NOT NULL,
  `id_chat` int(11) NOT NULL,
  `id_emisor` int(11) NOT NULL,
  `id_receptor` int(11) NOT NULL,
  `fecha_envio` datetime NOT NULL,
  `mensaje` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `notificaciones`
--

CREATE TABLE `notificaciones` (
  `id_notificacion` int(11) NOT NULL,
  `id_usuario` int(11) NOT NULL,
  `id_subasta` int(11) NOT NULL,
  `fecha_envio` datetime NOT NULL,
  `mensaje` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `roles`
--

CREATE TABLE `roles` (
  `id_rol` int(11) NOT NULL,
  `nombre` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `roles`
--

INSERT INTO `roles` (`id_rol`, `nombre`) VALUES
(1, 'Administrador'),
(2, 'Particular'),
(3, 'Empresa');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `rolesusuario`
--

CREATE TABLE `rolesusuario` (
  `usuario` int(11) NOT NULL,
  `rol` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `rolesusuario`
--

INSERT INTO `rolesusuario` (`usuario`, `rol`) VALUES
(1, 1),
(2, 2),
(3, 3);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `subastas`
--

CREATE TABLE `subastas` (
  `id_subasta` int(11) NOT NULL,
  `id_usuario` int(11) DEFAULT NULL,
  `titulo` varchar(255) DEFAULT NULL,
  `descripcion` text DEFAULT NULL,
  `fecha_inicio` datetime DEFAULT NULL,
  `fecha_fin` datetime DEFAULT NULL,
  `precio_inicial` decimal(10,2) DEFAULT NULL,
  `precio_actual` decimal(10,2) DEFAULT NULL,
  `id_ganador` int(11) DEFAULT NULL,
  `estado` varchar(15) DEFAULT NULL,
  `categoria` varchar(255) DEFAULT NULL,
  `estadoproducto` varchar(15) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `subastas`
--

INSERT INTO `subastas` (`id_subasta`, `id_usuario`, `titulo`, `descripcion`, `fecha_inicio`, `fecha_fin`, `precio_inicial`, `precio_actual`, `id_ganador`, `estado`, `categoria`, `estadoproducto`) VALUES
(8, 2, 'Mesa de cocina', 'Mesa de madera de alta calidad para seis personas', '2023-03-18 15:00:00', '2023-03-25 15:00:00', '300.00', '350.00', 2, '', 'Muebles', 'nuevo'),
(9, 2, 'Mesa de coche', 'Mesa de madera de alta calidad para seis personas', '2023-03-18 15:00:00', '2023-03-25 15:00:00', '300.00', '300.00', NULL, 'borrador', 'Muebles', 'nuevo'),
(10, 2, 'Pepe Viyuela', 'asfdf', '2123-12-18 04:21:00', '2023-04-27 21:31:00', '2312.00', '888888.00', 2, '', 'elPepe', 'usado'),
(11, 2, 'Prueba insertado', 'dwpdwowdo', '2023-03-18 03:11:00', '2023-03-25 02:11:00', '1009.00', '1009.00', NULL, 'borrador', 'prueba', 'usado'),
(12, 2, 'Comprobacion', 'sefserfs', '0000-00-00 00:00:00', '0000-00-00 00:00:00', '233.00', '233.00', NULL, 'cerrada', '3', 'usado'),
(13, 2, 'Comprobacion', 'sefserfs', '0000-00-00 00:00:00', '0000-00-00 00:00:00', '233.00', '233.00', NULL, 'cerrada', '3', 'usado'),
(14, 2, 'Prueba foto', 'aaasdasd', '2023-04-07 19:06:00', '2023-04-21 19:07:00', '2323.00', '235564.00', 2, '', '10', 'nuevo');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `usuarios`
--

CREATE TABLE `usuarios` (
  `id_usuario` int(11) NOT NULL,
  `nombreUsuario` varchar(30) NOT NULL,
  `nombre` varchar(50) NOT NULL,
  `email` varchar(50) NOT NULL,
  `password` varchar(70) NOT NULL,
  `fecha_registro` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `usuarios`
--

INSERT INTO `usuarios` (`id_usuario`, `nombreUsuario`, `nombre`, `email`, `password`, `fecha_registro`) VALUES
(1, 'admin', 'Administrador', 'Admin@example.com', '$2y$10$O3c1kBFa2yDK5F47IUqusOJmIANjHP6EiPyke5dD18ldJEow.e0eS', '2023-03-17 10:47:49'),
(2, 'particular', 'particular', 'particular@example.com', '$2y$10$uM6NtF.f6e.1Ffu2rMWYV.j.X8lhWq9l8PwJcs9/ioVKTGqink6DG', '2023-03-17 10:47:50'),
(3, 'Empresa', 'Empresa', 'Empresa@example.com', '$2y$10$uM6NtF.f6e.1Ffu2rMWYV.j.X8lhWq9l8PwJcs9/ioVKTGqink6DG', '2023-03-17 10:47:50');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `valoracionesproducto`
--

CREATE TABLE `valoracionesproducto` (
  `id_valoracion` int(11) NOT NULL,
  `id_usuario` int(11) NOT NULL,
  `id_subasta` int(11) DEFAULT NULL,
  `titulo_producto` varchar(255) DEFAULT NULL,
  `puntuacion` int(11) NOT NULL,
  `comentario` text DEFAULT NULL,
  `id_vendedor` int(11) DEFAULT NULL,
  `titulo_valoracion` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `valoracionesproducto`
--

INSERT INTO `valoracionesproducto` (`id_valoracion`, `id_usuario`, `id_subasta`, `titulo_producto`, `puntuacion`, `comentario`, `id_vendedor`, `titulo_valoracion`) VALUES
(3, 2, 8, 'Mesa de cocina', 222, 'aaaaa', 2, 'prueba de titulo');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `valoracionesvendedor`
--

CREATE TABLE `valoracionesvendedor` (
  `id_valoracion` int(11) NOT NULL,
  `id_usuario` int(11) NOT NULL,
  `puntuacion` int(11) NOT NULL,
  `comentario` text DEFAULT NULL,
  `id_vendedor` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `valoracionesvendedor`
--

INSERT INTO `valoracionesvendedor` (`id_valoracion`, `id_usuario`, `puntuacion`, `comentario`, `id_vendedor`) VALUES
(4, 2, 455, 'ss', 2);

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `categorias`
--
ALTER TABLE `categorias`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `chats`
--
ALTER TABLE `chats`
  ADD PRIMARY KEY (`id_chat`),
  ADD KEY `id_subasta_aso` (`id_subasta_aso`),
  ADD KEY `id_cliente1` (`id_cliente1`),
  ADD KEY `id_cliente2` (`id_cliente2`);

--
-- Indices de la tabla `imagenes`
--
ALTER TABLE `imagenes`
  ADD PRIMARY KEY (`id_imagen`),
  ADD KEY `fk_subasta` (`id_subasta`);

--
-- Indices de la tabla `mensajes`
--
ALTER TABLE `mensajes`
  ADD PRIMARY KEY (`id_mensaje`),
  ADD KEY `id_chat` (`id_chat`),
  ADD KEY `id_emisor` (`id_emisor`),
  ADD KEY `id_receptor` (`id_receptor`);

--
-- Indices de la tabla `notificaciones`
--
ALTER TABLE `notificaciones`
  ADD PRIMARY KEY (`id_notificacion`),
  ADD KEY `id_usuario` (`id_usuario`),
  ADD KEY `id_subasta` (`id_subasta`);

--
-- Indices de la tabla `roles`
--
ALTER TABLE `roles`
  ADD PRIMARY KEY (`id_rol`);

--
-- Indices de la tabla `rolesusuario`
--
ALTER TABLE `rolesusuario`
  ADD PRIMARY KEY (`usuario`,`rol`),
  ADD KEY `rol` (`rol`);

--
-- Indices de la tabla `subastas`
--
ALTER TABLE `subastas`
  ADD PRIMARY KEY (`id_subasta`);

--
-- Indices de la tabla `usuarios`
--
ALTER TABLE `usuarios`
  ADD PRIMARY KEY (`id_usuario`),
  ADD UNIQUE KEY `nombreUsuario` (`nombreUsuario`);

--
-- Indices de la tabla `valoracionesproducto`
--
ALTER TABLE `valoracionesproducto`
  ADD PRIMARY KEY (`id_valoracion`),
  ADD KEY `id_usuario` (`id_usuario`),
  ADD KEY `id_subasta` (`id_subasta`),
  ADD KEY `id_vendedor` (`id_vendedor`);

--
-- Indices de la tabla `valoracionesvendedor`
--
ALTER TABLE `valoracionesvendedor`
  ADD PRIMARY KEY (`id_valoracion`),
  ADD KEY `valoraciones_ibfk_1` (`id_usuario`),
  ADD KEY `valoraciones_ibfk_2` (`id_vendedor`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `categorias`
--
ALTER TABLE `categorias`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=16;

--
-- AUTO_INCREMENT de la tabla `chats`
--
ALTER TABLE `chats`
  MODIFY `id_chat` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `imagenes`
--
ALTER TABLE `imagenes`
  MODIFY `id_imagen` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT de la tabla `mensajes`
--
ALTER TABLE `mensajes`
  MODIFY `id_mensaje` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `notificaciones`
--
ALTER TABLE `notificaciones`
  MODIFY `id_notificacion` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `subastas`
--
ALTER TABLE `subastas`
  MODIFY `id_subasta` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;

--
-- AUTO_INCREMENT de la tabla `usuarios`
--
ALTER TABLE `usuarios`
  MODIFY `id_usuario` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT de la tabla `valoracionesproducto`
--
ALTER TABLE `valoracionesproducto`
  MODIFY `id_valoracion` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT de la tabla `valoracionesvendedor`
--
ALTER TABLE `valoracionesvendedor`
  MODIFY `id_valoracion` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- Restricciones para tablas volcadas
--

--
-- Filtros para la tabla `chats`
--
ALTER TABLE `chats`
  ADD CONSTRAINT `chats_ibfk_1` FOREIGN KEY (`id_subasta_aso`) REFERENCES `subastas` (`id_subasta`),
  ADD CONSTRAINT `chats_ibfk_2` FOREIGN KEY (`id_cliente1`) REFERENCES `usuarios` (`id_usuario`),
  ADD CONSTRAINT `chats_ibfk_3` FOREIGN KEY (`id_cliente2`) REFERENCES `usuarios` (`id_usuario`);

--
-- Filtros para la tabla `imagenes`
--
ALTER TABLE `imagenes`
  ADD CONSTRAINT `fk_subasta` FOREIGN KEY (`id_subasta`) REFERENCES `subastas` (`id_subasta`);

--
-- Filtros para la tabla `mensajes`
--
ALTER TABLE `mensajes`
  ADD CONSTRAINT `mensajes_ibfk_1` FOREIGN KEY (`id_chat`) REFERENCES `chats` (`id_chat`),
  ADD CONSTRAINT `mensajes_ibfk_2` FOREIGN KEY (`id_emisor`) REFERENCES `usuarios` (`id_usuario`),
  ADD CONSTRAINT `mensajes_ibfk_3` FOREIGN KEY (`id_receptor`) REFERENCES `usuarios` (`id_usuario`);

--
-- Filtros para la tabla `notificaciones`
--
ALTER TABLE `notificaciones`
  ADD CONSTRAINT `notificaciones_ibfk_1` FOREIGN KEY (`id_usuario`) REFERENCES `usuarios` (`id_usuario`),
  ADD CONSTRAINT `notificaciones_ibfk_2` FOREIGN KEY (`id_subasta`) REFERENCES `subastas` (`id_subasta`);

--
-- Filtros para la tabla `rolesusuario`
--
ALTER TABLE `rolesusuario`
  ADD CONSTRAINT `rolesusuario_ibfk_1` FOREIGN KEY (`rol`) REFERENCES `roles` (`id_rol`);

--
-- Filtros para la tabla `valoracionesproducto`
--
ALTER TABLE `valoracionesproducto`
  ADD CONSTRAINT `valoracionesproducto_ibfk_1` FOREIGN KEY (`id_usuario`) REFERENCES `usuarios` (`id_usuario`),
  ADD CONSTRAINT `valoracionesproducto_ibfk_2` FOREIGN KEY (`id_vendedor`) REFERENCES `usuarios` (`id_usuario`);

--
-- Filtros para la tabla `valoracionesvendedor`
--
ALTER TABLE `valoracionesvendedor`
  ADD CONSTRAINT `valoraciones_ibfk_1` FOREIGN KEY (`id_usuario`) REFERENCES `usuarios` (`id_usuario`),
  ADD CONSTRAINT `valoraciones_ibfk_2` FOREIGN KEY (`id_vendedor`) REFERENCES `usuarios` (`id_usuario`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
